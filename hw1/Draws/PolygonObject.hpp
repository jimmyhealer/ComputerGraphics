class PolygonObject : public DrawObject {
protected:
  std::vector<std::pair<float, float> > points;
  std::vector<std::pair<float, float> > unclosed_points;
  float line_width;
  bool is_closed = false;
  int full_mode;
  RGBAColor color;
  bool _checkClosed(float x, float y) {
    if(unclosed_points.size() == 0) return false;
    float x0 = unclosed_points[0].first;
    float y0 = unclosed_points[0].second;
    if(abs(x - x0) + abs(y - y0) <= 8) {
      return true;
    }
    return false;
  }
public:
  PolygonObject(float x, float y) {
    this->line_width = g_line_width;
    this->color = RGBAColor(g_now_color);
    this->full_mode = is_full_mode ? GL_FILL : GL_LINE;
    this->addPoint(x, y);
  }
  void addPoint(float x, float y) {
    if(!_checkClosed(x, y)) {
      unclosed_points.push_back({x, y});
    }
    else {
      is_closed = true;
      points = unclosed_points;
      unclosed_points.clear();   
    }
  }
  bool isClosed() {
    return is_closed;
  }
  void draw() override {
    glColor3f(color.r, color.g, color.b);
    glLineWidth(line_width);
    if(is_closed) {
      glPolygonMode(GL_FRONT_AND_BACK, full_mode);
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