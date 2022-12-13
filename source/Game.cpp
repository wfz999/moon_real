//
//  Game.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "Game.h"
bool Game::CheckCollision(Ship* &one, Asteroid* &two) // AABB - AABB collision
{
//    int xx = abs(one->ship_pos[0].x- one->ship_pos[2].x);
//    std::cout<<"xx:"<<one->ship_pos[0].x- one->ship_pos[2].x;
    // collision x-axis?
    bool collisionX = one->state.cur_location.x + (one->ship_pos[2].x- one->ship_pos[0].x)>= two->state.cur_location.x &&
    two->state.cur_location.x + (two->asteroid_bbox[1].x -two->asteroid_bbox[0].x )>= one->state.cur_location.x;
    // collision y-axis?
    bool collisionY = one->state.cur_location.y + (one->ship_pos[1].y- one->ship_pos[0].y) >= two->state.cur_location.y &&
    two->state.cur_location.y + (two->asteroid_bbox[1].y -two->asteroid_bbox[0].y ) >= one->state.cur_location.y;
    if(collisionX && collisionY == true){
        game_over = true;
    }
    // collision only if on both axes
    return collisionX && collisionY;
}

bool Game::testIntersections(Ship *ship,std::vector <Asteroid *> asteroids, Bullets bullets){
    //    My method is to check whether the four vetices of the ship are within the asteroids.
    int min_ship_x =0;
    int min_ship_y =0;
    int max_ship_x =0;
    int max_ship_y =0;
    
    std::vector < vec2 > ship_pos_new;
    ship_pos_new.resize(4);
//    std::cout<<'ship_pos:'<<sizeof(ship->ship_pos)/sizeof(ship->ship_pos[0]);
    if(!ship->state.thruster_on && ship->state.turning == Ship::_NO_TURN){
//      glBindTexture( GL_TEXTURE_2D, GLvars.ship_texture );
//      glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
        ship_pos_new[0]=ship->ship_pos[0];
        ship_pos_new[1]=ship->ship_pos[1];
        ship_pos_new[2]=ship->ship_pos[2];
        ship_pos_new[3]=ship->ship_pos[3];
    }
    
    if(ship->state.thruster_on && ship->state.turning == Ship::_NO_TURN){
//      glBindTexture( GL_TEXTURE_2D, GLvars.ship_t_texture );
//      glDrawArrays( GL_TRIANGLE_STRIP, 4, 4 );
        ship_pos_new[0]=ship->ship_pos[4];
        ship_pos_new[1]=ship->ship_pos[5];
        ship_pos_new[2]=ship->ship_pos[6];
        ship_pos_new[3]=ship->ship_pos[7];
    }
    
    if(!ship->state.thruster_on && ship->state.turning == Ship::_TURN_LEFT){
//      glBindTexture( GL_TEXTURE_2D, GLvars.left_texture );
//      glDrawArrays( GL_TRIANGLE_STRIP, 8, 4 );
        ship_pos_new[0]=ship->ship_pos[8];
        ship_pos_new[1]=ship->ship_pos[9];
        ship_pos_new[2]=ship->ship_pos[10];
        ship_pos_new[3]=ship->ship_pos[11];
    }
    
    if(!ship->state.thruster_on && ship->state.turning == Ship::_TURN_RIGHT){
//      glBindTexture( GL_TEXTURE_2D, GLvars.right_texture  );
//      glDrawArrays( GL_TRIANGLE_STRIP, 8, 4 );
        ship_pos_new[0]=ship->ship_pos[8];
        ship_pos_new[1]=ship->ship_pos[9];
        ship_pos_new[2]=ship->ship_pos[10];
        ship_pos_new[3]=ship->ship_pos[11];
    }
    
    if(ship->state.thruster_on && ship->state.turning == Ship::_TURN_LEFT){
//      glBindTexture( GL_TEXTURE_2D, GLvars.left_t_texture );
//      glDrawArrays( GL_TRIANGLE_STRIP, 12, 4 );
        ship_pos_new[0]=ship->ship_pos[12];
        ship_pos_new[1]=ship->ship_pos[13];
        ship_pos_new[2]=ship->ship_pos[14];
        ship_pos_new[3]=ship->ship_pos[15];
    }

    if(ship->state.thruster_on && ship->state.turning == Ship::_TURN_RIGHT){
//      glBindTexture( GL_TEXTURE_2D, GLvars.right_t_texture  );
//      glDrawArrays( GL_TRIANGLE_STRIP, 12, 4 );
        ship_pos_new[0]=ship->ship_pos[12];
        ship_pos_new[1]=ship->ship_pos[13];
        ship_pos_new[2]=ship->ship_pos[14];
        ship_pos_new[3]=ship->ship_pos[15];
    }
    
    mat4 ModelView = Translate(ship->state.cur_location.x, ship->state.cur_location.y, 0)
                     * RotateZ(ship->state.angle);
    std::vector < vec4 > ship_pos_new_4;
    ship_pos_new_4.resize(4);
    ship_pos_new_4[0]=vec4(ship_pos_new[0].x,ship_pos_new[0].y,0,0);
    ship_pos_new_4[1]=vec4(ship_pos_new[1].x,ship_pos_new[1].y,0,0);
    ship_pos_new_4[2]=vec4(ship_pos_new[2].x,ship_pos_new[2].y,0,0);
    ship_pos_new_4[3]=vec4(ship_pos_new[3].x,ship_pos_new[3].y,0,0);
//    Game();
//    glfwGetWindowSize(window, &width, &height);
//    mat4 proj = Ortho2D(game->screen_extents[0],game->screen_extents[1],
//                        game->screen_extents[2],game->screen_extents[3]);
    
//    glUniformMatrix4fv( ship_pos_new, 1, GL_TRUE, proj*ModelView);
//    std::cout<<"ModelView: "<<ModelView;
//    std::cout<<"ship_pos_new_4: "<<ship_pos_new_4[0];
////    ship_pos_new = ModelView*ship_pos_new_4;
//    std::cout<<"ship_pos_new: "<<&ship_pos_new;
    
//    for(int i;i<)
//    ship.ship_pos
    bool result=false;
    for(int i=0;i<2;i++){
        result = CheckCollision(ship,asteroids[i]);
    }
    
//    std::cout<<"collision:"<<result;
  //TODO
  return result;
}

Game::Game(){
  ship = new Ship();
  asteroids.resize(2);
  asteroids[0] = new Asteroid(1);
  asteroids[1] = new Asteroid(2);
//  asteroids[2] = new Asteroid(2);
//  asteroids[3] = new Asteroid(1);
//  asteroids[4] = new Asteroid(2);
//  asteroids[5] = new Asteroid(1);
//  asteroids[6] = new Asteroid(2);
//  asteroids[7] = new Asteroid(1);
//  asteroids[8] = new Asteroid(2);
//  asteroids[9] = new Asteroid(1);
  
  game_over = false;
  
  std::string file_location = source_path + "sprites/game_over.png";
  unsigned error = lodepng::decode(game_over_im, go_width, go_height, file_location.c_str());
  std::cout << go_width << " X " << go_height << " game image loaded\n";
  
};


void Game::gl_init(){
  
  std::vector <vec2> pos(4);
  std::vector <vec2> uv(4);
  
  pos[0] = vec2(screen_extents[0],  screen_extents[3]);
  pos[1] = vec2(screen_extents[0],  screen_extents[2]);
  pos[2] = vec2(screen_extents[1],  screen_extents[3]);
  pos[3] = vec2(screen_extents[1],  screen_extents[2]);
  
  uv[0] = vec2(0.0,0.0);
  uv[1] = vec2(0.0,1.0);
  uv[2] = vec2(1.0,0.0);
  uv[3] = vec2(1.0,1.0);
  

  unsigned int vert_size = pos.size()*sizeof(vec2);
  unsigned int uv_size = uv.size()*sizeof(vec2);

  std::string vshader = source_path + "shaders/vshader_Texture.glsl";
  std::string fshader = source_path + "shaders/fshader_Texture.glsl";

  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());

  GOGLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GOGLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GOGLvars.vertex_shader);
  check_shader_compilation(vshader, GOGLvars.vertex_shader);

  GOGLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GOGLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GOGLvars.fragment_shader);
  check_shader_compilation(fshader, GOGLvars.fragment_shader);

  GOGLvars.program = glCreateProgram();
  glAttachShader(GOGLvars.program, GOGLvars.vertex_shader);
  glAttachShader(GOGLvars.program, GOGLvars.fragment_shader);

  glLinkProgram(GOGLvars.program);
  check_program_link(GOGLvars.program);
  glUseProgram(GOGLvars.program);
  
  glBindFragDataLocation(GOGLvars.program, 0, "fragColor");

  GOGLvars.vpos_location   = glGetAttribLocation(GOGLvars.program, "vPos");
  GOGLvars.vtex_location = glGetAttribLocation(GOGLvars.program, "vTexCoord" );
  GOGLvars.M_location = glGetUniformLocation(GOGLvars.program, "M" );
  
  glGenTextures( 1, &GOGLvars.texture );

  glBindTexture( GL_TEXTURE_2D, GOGLvars.texture );
  glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, go_width, go_height,
               0, GL_RGBA, GL_UNSIGNED_BYTE, &game_over_im[0]);
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
  glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );


  // Create a vertex array object
  glGenVertexArrays( 1, &GOGLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GOGLvars.vao );

  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GOGLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GOGLvars.buffer );

  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, vert_size + uv_size, NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, vert_size, &pos[0] );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, vert_size, uv_size, &uv[0] );

  glEnableVertexAttribArray(GOGLvars.vpos_location);
  glEnableVertexAttribArray(GOGLvars.vtex_location );

  glVertexAttribPointer( GOGLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GOGLvars.vtex_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(vert_size) );

  glBindVertexArray(0);
  
}

void Game::draw_game_over(mat4 proj){
  
  glUseProgram(GOGLvars.program);
  glBindVertexArray( GOGLvars.vao );
  glBindBuffer( GL_ARRAY_BUFFER, GOGLvars.buffer );
  
  glUniformMatrix4fv( GOGLvars.M_location, 1, GL_TRUE, proj);
  
  glBindTexture( GL_TEXTURE_2D, GOGLvars.texture  );
  glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
  
  glBindVertexArray(0);
  glBindBuffer( GL_ARRAY_BUFFER, 0);

//  glfwSetWindowShouldClose(window, GLFW_TRUE);
    game_over = true;        
}
