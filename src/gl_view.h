#ifndef gl_view_h
#define gl_view_h

#define NOMINMAX
#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <FL/Fl_File_Icon.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Shared_Image.H>


#include <Eigen/StdVector>

#include <stdlib.h>
#include <stdio.h>
#include <vector>


class glView;
#include "ui.h"

//Project includes
#include <skeleton.hpp>
#include <skin.hpp>

using namespace std;
using namespace Eigen;
using namespace Skeletal;

class UserInterface;
class glView : public Fl_Gl_Window 
{

public:
  
  glView(int x,int y,int w,int h,const char *l=0);

  // overrides of important window things
  virtual int handle(int);
  virtual void draw();  
  void display();
  void drawScene();
  void initScene();
  void draw_skeleton(double t, bool disable_color = false, float alpha = 1.0);
  void draw_frame(int f);
  void drawFloor(bool backface = false);
  void updateCamera();
  void updateAutoCamera();

  void set_ui(UserInterface* ui){m_ui = ui;};
  void select_animation(int index);

  // callback functions
  void toggle_play(int value){m_play = value;redraw();};
  void toggle_repeat(int value){m_repeat = value;redraw();};
  void move_frame_to(int value);
  void set_desired_fps(int value){m_play_fps = value; redraw();};
  void load_file();
  void remove_file();
  void update_selection();
  void print_skeleton(const Joint& skel, int t = 0);
  void add_animation_list();
  void del_animation_list();
  void mode_single();
  void mode_multiple();
  void update_concat_times();
  void reload_concat_times();

public:
  enum CAMERA_MODE
  {
    CAMERA_FREE,
    CAMERA_AUTO
  };
  enum DRAW_STYLE
  {
    STYLE_LINES,
    STYLE_ELLIPSOIDS,
    STYLE_STICK,
    STYLE_STICK2,
    STYLE_STICK2_NO_FACE,
    STYLE_STICK2_EDGES,
    STYLE_STICK2_CUSTOM_FACE
  };

public:
  bool m_drawing;
  bool m_play;
  bool m_repeat;
  bool m_draw_shadow;
  bool m_draw_reflection;
  bool m_draw_preview;
  bool m_draw_fps;
  int m_camera_mode;
  int m_draw_style; 
  unsigned int m_frame_num;
  UserInterface* m_ui;
  float m_time;
  float m_play_fps;

  Fl_File_Chooser* file_chooser; 
  vector<Motion*> mocap_list;
  Motion* mocap_selected;
  Motion mocap_combine;

  GLuint idFloor;
  GLuint idFace;
  GLfloat lightPosition[4];
  GLfloat floorPlaneEquation[4];


};


#endif