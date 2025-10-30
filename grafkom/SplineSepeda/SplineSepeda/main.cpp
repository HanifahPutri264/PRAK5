#include <iostream>
#include <fstream>

struct Point {
    float x, y;
};

Point bezier(float t, Point p0, Point p1, Point p2, Point p3) {
    float u = 1 - t;
    float tt = t * t;
    float uu = u * u;
    float uuu = uu * u;
    float ttt = tt * t;

    Point p;
    p.x = uuu * p0.x + 3 * uu * t * p1.x + 3 * u * tt * p2.x + ttt * p3.x;
    p.y = uuu * p0.y + 3 * uu * t * p1.y + 3 * u * tt * p2.y + ttt * p3.y;
    return p;
}

int main() {
    Point p0 = {0.0, 0.0};
    Point p1 = {0.2, 0.5};
    Point p2 = {0.8, 0.5};
    Point p3 = {1.0, 0.0};

    std::ofstream objFile("rangka.obj");
    if (!objFile.is_open()) {
        std::cerr << "Gagal membuat file .obj" << std::endl;
        return 1;
    }

    objFile << "# Rangka Sepeda dari Bezier Curve\n";

    int index = 1;
    for (float t = 0; t <= 1.001; t += 0.05) {
        Point p = bezier(t, p0, p1, p2, p3);
        objFile << "v " << p.x << " " << p.y << " 0.0\n";
        index++;
    }

    objFile << "l";
    for (int i = 1; i < index; ++i) {
        objFile << " " << i;
    }
    objFile << "\n";

    objFile.close();
    std::cout << "File rangka.obj berhasil dibuat.\n";
    return 0;
}
