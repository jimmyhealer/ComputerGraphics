class DrawObject {
protected:
  float x, y;
public:
  DrawObject() {}
  DrawObject(float x_, float y_) : x(x_), y(y_) {}
  virtual void draw() = 0;
};