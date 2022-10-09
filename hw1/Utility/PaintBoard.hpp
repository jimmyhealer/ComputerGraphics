int paint_board_width = 512;
int paint_board_height = 512;
int paint_board_x = 120;
int paint_board_y = 0;

namespace PaintBoard {
  void update(float width, float height) {
    paint_board_width = width - paint_board_x;
    paint_board_height = height - paint_board_y - 90;
  }

  bool isInside(float x, float y) {
    return x >= paint_board_x && x <= paint_board_x + paint_board_width && y >= paint_board_y && y <= paint_board_y + paint_board_height;
  }

  std::pair<float, float> getCanDrawRange(float x, float y) {
    if(x < paint_board_x) x = paint_board_x;
    if(x > paint_board_x + paint_board_width) x = paint_board_x + paint_board_width;
    if(y < paint_board_y) y = paint_board_y;
    if(y > paint_board_y + paint_board_height) y = paint_board_y + paint_board_height;
    return {x, y};
  }

  float getCanDrawRange(float x, float y, float radius) {
    if(x < paint_board_x) x = paint_board_x;
    if(x > paint_board_x + paint_board_width) x = paint_board_x + paint_board_width;
    if(y < paint_board_y) y = paint_board_y;
    if(y > paint_board_y + paint_board_height) y = paint_board_y + paint_board_height;
    if(x - radius < paint_board_x) radius = x - paint_board_x;
    if(x + radius > paint_board_x + paint_board_width) radius = paint_board_x + paint_board_width - x;
    if(y - radius < paint_board_y) radius = y - paint_board_y;
    if(y + radius > paint_board_y + paint_board_height) radius = paint_board_y + paint_board_height - y;
    return radius;
  }

  void SaveAsBMP(const char *fileName) {
    FILE *file;
    unsigned long imageSize;
    GLbyte *data=NULL;
    GLint viewPort[4];
    GLenum lastBuffer;
    BITMAPFILEHEADER bmfh;
    BITMAPINFOHEADER bmih;
    bmfh.bfType = 'MB', bmfh.bfReserved1 = 0, bmfh.bfReserved2 = 0, bmfh.bfOffBits = 54;
    viewPort[0] = paint_board_x, viewPort[1] = paint_board_y, viewPort[2] = paint_board_width, viewPort[3] = paint_board_height;
    imageSize = ((viewPort[2] + (( 4 - (viewPort[2] % 4)) % 4)) * viewPort[3] * 3) + 2;
    bmfh.bfSize = imageSize + sizeof(bmfh) + sizeof(bmih);
    data = new GLbyte[imageSize];
    glPixelStorei(GL_PACK_ALIGNMENT, 4);
    glPixelStorei(GL_PACK_ROW_LENGTH, 0);
    glPixelStorei(GL_PACK_SKIP_ROWS, 0);
    glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_PACK_SWAP_BYTES, 1);
    glGetIntegerv(GL_READ_BUFFER, (GLint*) &lastBuffer);
    glReadBuffer(GL_FRONT);
    glReadPixels(viewPort[0], viewPort[1], viewPort[2], viewPort[3], GL_BGR, GL_UNSIGNED_BYTE, data);
    data[imageSize - 1]=0;
    data[imageSize - 2]=0;
    glReadBuffer(lastBuffer);
    file = fopen(fileName,"wb");
    bmih.biSize = 40;
    bmih.biWidth = viewPort[2];
    bmih.biHeight = viewPort[3];
    bmih.biPlanes = 1;
    bmih.biBitCount = 24;
    bmih.biCompression = 0;
    bmih.biSizeImage = imageSize;
    bmih.biXPelsPerMeter = 45089;
    bmih.biYPelsPerMeter = 45089;
    bmih.biClrUsed = 0;
    bmih.biClrImportant = 0;
    fwrite(&bmfh, sizeof(bmfh), 1, file);
    fwrite(&bmih, sizeof(bmih), 1, file);
    fwrite(data, imageSize, 1, file);
    delete data;
    fclose(file);
  }

  void save() {
    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    string filename = "save_" + std::to_string(time) + ".bmp";
    PaintBoard::SaveAsBMP(filename.c_str());
  }
}