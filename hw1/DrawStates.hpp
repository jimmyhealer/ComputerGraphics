class DrawStates {
private:
  std::vector<DrawObject*> presistence_objects;
  std::vector<DrawObject*> draw_objects;
  DrawObject* paint_board_object;
  DrawObject* tmp_object = nullptr;
public:
  void add(DrawObject* obj, bool is_presistence=true) {
    if(is_presistence) {
      presistence_objects.push_back(obj);
    } 
    else {
      draw_objects.push_back(obj);
    }
    is_changed = true;
  }
  void addTmpObject(DrawObject* obj) {
    tmp_object = obj;
    is_changed = true;
  }
  void clear() {
    draw_objects.clear();
    is_changed = true;
  }
  void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if(tmp_object != nullptr) {
      glRasterPos2i(0, 0);
      glDrawPixels(window_width, window_height, GL_RGBA, GL_UNSIGNED_BYTE, window_data);
      tmp_object->draw();
      tmp_object = nullptr;
      if(is_open_grid) PaintBoard::draw();
    }
    else {
      for(DrawObject* obj : draw_objects) {
        obj->draw();
      }
      if(is_open_grid) PaintBoard::draw();
      for(DrawObject* obj : presistence_objects) {
        obj->draw();
      }
    }
    glFlush();
    glutSwapBuffers();
  }
};

class DrawStatePresistence {
private:
  std::deque<DrawStates> presistence;
  int version = 0;
public:
  void add(DrawObject* obj, bool is_initial=false) {
    if(version > 64) {
      presistence.pop_front();
      version--;
    }
    if(is_initial == true) {
      if(presistence.size() > 0) {
        presistence[version].add(obj, true);
      }
      else {
        DrawStates tmp;
        tmp.add(obj, true);
        presistence.push_back(tmp);
      }
    }
    else{
      if(presistence.size() - 1 != version) {
        presistence.erase(presistence.begin() + version + 1, presistence.end());
      }
      DrawStates tmp = presistence.back();
      tmp.add(obj, false);
      presistence.push_back(tmp);
      version++;
    }
  }
  void addTmpObject(DrawObject* obj) {
    presistence[version].addTmpObject(obj);
  }
  void clear() {
    if(presistence.size() == version) {
      DrawStates draw_state;
      draw_state.clear();
      presistence.push_back(draw_state);
    }
    else {
      presistence[version].clear();
    }
  }
  void display() {
    presistence[version].display();
  }
  void undo() {
    if(now_draw_object == nullptr && version > 0) {
      version--;
      polygon = nullptr;
      is_changed = true;
    }
  }
  void redo() {
    if(polygon == nullptr && version < presistence.size() - 1) {
      version++;
      is_changed = true;
    }
  }
};
