class RGBAColor {
public:
  float r, g, b;
  float a;
  RGBAColor() {}
  RGBAColor(int color) {
    switch(color) {
      case COLOR::RED:
        r = 1.0; g = 0.0; b = 0.0, a = 1.0;
        break;
      case COLOR::GREEN:
        r = 0.0; g = 1.0; b = 0.0, a = 1.0;
        break;
      case COLOR::BLUE:
        r = 0.0; g = 0.0; b = 1.0, a = 1.0;
        break;
      case COLOR::BLACK:
        r = 0.0; g = 0.0; b = 0.0, a = 1.0;
        break;
      case COLOR::WHITE:
        r = 1.0; g = 1.0; b = 1.0, a = 1.0;
        break;
      default:
        r = 0.0; g = 0.0; b = 0.0, a = 1.0;
        break;
    }
  }
  RGBAColor(float r_, float g_, float b_, float a_) :
     r(r_), g(g_), b(b_), a(a_) {}
};