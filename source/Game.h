//
//  Game.h
//  Asteroids
//
//  Created by Brian Summa on 9/7/15.
//
//

#ifndef Asteroids_Game_h
#define Asteroids_Game_h

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

#include <list>
#include <vector>
#include <utils/shader_process.h>
#include <path/path.h>

#include <utils/vec.h>
#include <utils/mat.h>
#include <utils/lodepng.h>
#include <utils/loadTexture.h>


#include "Bullets.h"
#include "Ship.h"
#include "Asteroid.h"
#include "Background.h"

class Game{

public:
  Ship *ship;
  std::vector <Asteroid *> asteroids;
  Bullets bullets;

  //left right bottom top of window
  vec4 screen_extents;
    
    bool game_over;
  
private:
  
  
  
  std::vector<unsigned char> game_over_im;
  unsigned go_width, go_height;

  struct {
    GLuint vao;           //Vertex array object
    GLuint program;       //shader program
    GLuint buffer;        //Vertex buffer objects
    GLuint vertex_shader, fragment_shader;  //Shaders
    GLint vpos_location, vtex_location;   //reference to pos and color in shaders
    GLint M_location;     //Reference to matrix in shader
    GLuint texture;
  } GOGLvars;

  
public:
  Game();
  Game *game;
  ~Game(){
    delete ship;
    asteroids.clear();
  }
  
  void init(){
    for(unsigned int i=0; i < asteroids.size(); i++){
      asteroids[i]->gl_init();
    }
    ship->gl_init();
    bullets.gl_init();
    gl_init();
  }
  
  void draw(mat4 proj){
    ship->draw(proj);
    bullets.draw(proj);
    for(unsigned int i=0; i < asteroids.size(); i++){
      asteroids[i]->draw(proj);
    }
    
    if(game_over){
      draw_game_over(proj);
    }
  }
  
  void update(){
//    std::cout<<"jump:"<<ship->jump_;
      if(ship->jump_>5){
          for(unsigned int i=0; i < asteroids.size(); i++){
            asteroids[i]->update_state(screen_extents);
          }
          ship->update_state(screen_extents);
          bullets.update_state(screen_extents);

      //    tcg::vec2 ship_velocity = - ship->state.velocity;

          ship->state.cur_location-=ship->state.velocity;
          for(unsigned int i=0; i < asteroids.size(); i++){
              asteroids[i]->state.cur_location-=ship->state.velocity;
          }
      //      for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end();){
      //          it->state.cur_location-=ship->state.velocity;
      //      }
          ship->state.cur_location+=vec2(0.0f,0.03f);
          game_over = testIntersections(ship,asteroids,bullets);
          ship->jump_--;
//          std::cout<<"jump:"<<ship->jump_;
//          std::cout<<"v:"<<ship->state.velocity;
      }else if(ship->jump_>0){
          for(unsigned int i=0; i < asteroids.size(); i++){
            asteroids[i]->update_state(screen_extents);
          }
          ship->update_state(screen_extents);
          bullets.update_state(screen_extents);

      //    tcg::vec2 ship_velocity = - ship->state.velocity;

          ship->state.cur_location-=ship->state.velocity;
          for(unsigned int i=0; i < asteroids.size(); i++){
              asteroids[i]->state.cur_location-=ship->state.velocity;
          }
      //      for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end();){
      //          it->state.cur_location-=ship->state.velocity;
      //      }
          ship->state.cur_location-=vec2(0.0f,0.03f);
          game_over = testIntersections(ship,asteroids,bullets);
          ship->jump_--;
      }else{
          for(unsigned int i=0; i < asteroids.size(); i++){
            asteroids[i]->update_state(screen_extents);
          }
          ship->update_state(screen_extents);
          bullets.update_state(screen_extents);

      //    tcg::vec2 ship_velocity = - ship->state.velocity;

//          ship->state.cur_location.y=0.0;
            ship->state.cur_location-=ship->state.velocity;
          for(unsigned int i=0; i < asteroids.size(); i++){
              asteroids[i]->state.cur_location-=ship->state.velocity;
          }
      //      for (std::list<Bullet>::iterator it = bullets.begin(); it != bullets.end();){
      //          it->state.cur_location-=ship->state.velocity;
      //      }

          game_over = testIntersections(ship,asteroids,bullets);
      }
      
  }
  
private:
  
  void gl_init();
  void draw_game_over(mat4 proj);
  
  bool testIntersections(Ship *ship,std::vector <Asteroid *> asteroids,Bullets bullets);
    bool CheckCollision(Ship* &one, Asteroid* &two);
  
};


#endif
