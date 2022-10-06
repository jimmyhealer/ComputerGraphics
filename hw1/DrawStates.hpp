class DrawStates {
private:
  std::vector<DrawObject*> presistence_objects;
  std::vector<DrawObject*> draw_objects;
  DrawObject* tmp_object = nullptr;
public:
  void add(DrawObject* obj, bool is_presistence=true) {
    draw_objects.push_back(obj);
  }
  void addTmpObject(DrawObject* obj) {
    tmp_object = obj;
    glutPostRedisplay();
  }
  void display() {
    glClearColor(1,1,1,1);
    static int times = 0;
    std::cerr << "times " << times++ << '\n'; 
    glClear(GL_COLOR_BUFFER_BIT);
    for(DrawObject* obj : draw_objects) {
      obj->draw();
    }
    if(tmp_object != nullptr) {
      tmp_object->draw();
      tmp_object = nullptr;
    }
    glFlush();
  }
} draw_state;

