class PlaneObject : public UIObject {
private:
  std::vector<UIObject*> item_objects;
  int item_is_clicked = -1;
public:
  PlaneObject() {};
  PlaneObject(
    float x_, float y_, 
    float width_, float height_, RGBAColor color_) :
    UIObject(x_, y_, width_, height_, color_) {};
  void addItem(UIObject* item, bool clicked=false) {
    item_objects.push_back(item);
    if(clicked) {
      item_is_clicked = item_objects.size() - 1;
    }
  }
  void update(int width, int height) {
    this->width = width;
    this->height = height;
  }
  void update(int x, int y, int width, int height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
  }
  void toggleVisibility() {
    this->is_visible = !this->is_visible;
    for(auto item: item_objects) {
      item->toggleVisibility();
    }
  }
  void setVisibility(bool is_visible) {
    this->is_visible = is_visible;
    for(auto item: item_objects) {
      item->setVisibility(is_visible);
    }
  }
  void draw() override {
    if (!isVisible()) return;
    glColor3f(color.r, color.g, color.b);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
    for (int i = 0; i < item_objects.size(); i++) {
      item_objects[i]->setIsClicked(item_is_clicked == i);
      item_objects[i]->draw();
    }
  }
  bool isClickItem(int x_, int y_, bool is_clicked=true) {
    for (int i = 0; i < item_objects.size(); i++) {
      if (item_objects[i]->isInside(x_, y_)) {
        item_objects[i]->click(x_, y_);
        item_is_clicked = i;
        return true;
      }
    }
    if(!is_clicked) item_is_clicked = -1;
    return false;
  }
  bool isInsideItem(int x_, int y_) {
    for (int i = 0; i < item_objects.size(); i++) {
      if (item_objects[i]->isInside(x_, y_)) {
        return true;
      }
    }
    return false;
  }
  void click(float x=0, float y=0) override {}
  void addPoint(float x, float y) override {} 
};