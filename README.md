# IGraphics

This is the repository for the **IGraphics** library.  
IGraphics is a thin wrapper on top of OpenGL.  
It can be used for simple **2D graphics demonstrations** and **C programming course projects**.

---

## 🔹 Command Line Compilation

```sh
g++ -IOpenGL\include -w -c BallDemo.cpp -o BallDemo.o
```

## 🔹 Command Line Linking

```sh
g++ -LOpenGL\lib BallDemo.o -o BallDemo.exe -lGlaux -lGLU32 -lglui32 -lglut32 -lOPENGL32 -lgdi32
```

## 🔹 Command Line Running

- Ensure **glut32.dll** is present in the same folder.  
- Run the executable:

```sh
BallDemo.exe
```

---

## 🔹 Animation Related API

```cpp
int iSetTimer(int msec, void (*f)(void));
void iPauseTimer(int index);
void iResumeTimer(int index);
```

---

## 🔹 Shape Drawing

```cpp
void iSetColor(double r, double g, double b);
void iPoint(double x, double y, int size=0);
void iLine(double x1, double y1, double x2, double y2);
void iFilledPolygon(double x[], double y[], int n);
void iPolygon(double x[], double y[], int n);
void iRectangle(double left, double bottom, double dx, double dy);
void iFilledRectangle(double left, double bottom, double dx, double dy);
void iFilledCircle(double x, double y, double r, int slices=100);
void iCircle(double x, double y, double r, int slices=100);
void iEllipse(double x, double y, double a, double b, int slices=100);
void iFilledEllipse(double x, double y, double a, double b, int slices=100);
```

---

## 🔹 Text Output

```cpp
void iText(double x, double y, char *str, void* font=GLUT_BITMAP_8_BY_13);
```

---

## 🔹 Rendering Functions

```cpp
void iDraw();
void iClear();
void iShowBMP(int x, int y, char filename[]);
```

---

## 🔹 Initialization

```cpp
void iInitialize(int width=500, int height=500, char *title="iGraphics");
```

---

## 🔹 I/O Event Handling

```cpp
void iKeyboard(unsigned char);
void iSpecialKeyboard(unsigned char);
void iMouseMove(int, int);
void iMouse(int button, int state, int x, int y);
```

---

### 🎯 **Usage**  
IGraphics simplifies **2D graphics programming** using OpenGL.  
It is particularly useful for **educational projects** and **simple graphics demonstrations**.

---
