class PolygonObject : public DrawObject {
protected:
  std::vector<std::pair<float, float> > points;
  std::vector<std::pair<float, float> > unclosed_points;
  float line_width;
  bool is_closed = false;
  RGBAColor color;
public:
  PolygonObject() {}
  PolygonObject(
    float x, float y,
    float line_width_,
    RGBAColor color_) : DrawObject(0.0, 0.0) {
    unclosed_points.push_back({x, y});
    color = color_;
    line_width = line_width_;
  }
  void add(float x, float y, bool is_closed_=false) {
    unclosed_points.push_back({x, y});
    if(is_closed_) {
      points.insert(points.end(), unclosed_points.begin(), unclosed_points.end());
      is_closed = true;
    }
    is_changed = true;
    // draw_state_presistence.display();
  }
  bool checkClosed(float x, float y) {
    if(unclosed_points.size() == 0) return false;
    float x0 = unclosed_points[0].first;
    float y0 = unclosed_points[0].second;
    if(abs(x - x0) + abs(y - y0) <= 8) {
      return true;
    }
    return false;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glLineWidth(line_width);
    if(is_closed) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glBegin(GL_POLYGON);
      for(auto point : points) {
        glVertex2f(point.first, point.second);
      }
    } 
    else if((int)unclosed_points.size() >= 2) {
      glBegin(GL_LINE_STRIP);
      for(auto point : unclosed_points) {
        glVertex2f(point.first, point.second);
      }
    }
    glEnd();
  }
};