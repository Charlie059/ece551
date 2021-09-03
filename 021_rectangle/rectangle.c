#include <stdio.h>
#include <stdlib.h>
//I've provided "min" and "max" functions in
//case they are useful to you
int min(int a, int b) {
  if (a < b) {
    return a;
  }
  return b;
}
int max(int a, int b) {
  if (a > b) {
    return a;
  }
  return b;
}

//Declare your rectangle structure here!
struct rectangle_ {
  int x;
  int y;
  int width;
  int height;
};

struct line_ {
  int point;
  int length;
};
typedef struct rectangle_ rectangle;
typedef struct line_ line;

rectangle canonicalize(rectangle r) {
  //WRITE THIS FUNCTION
  if (r.width < 0) {
    r.x += r.width;
    r.width *= -1;
  }

  if (r.height < 0) {
    r.y += r.height;
    r.height *= -1;
  }
  return r;
}

int between(int a_start, int a_end, int b) {
  if (a_start <= b && b <= a_end)
    return 1;
  else
    return 0;
}

line cal_inter(rectangle r1, rectangle r2, int mode) {
  line inter;
  if (mode == 0) {
    int point1_start = r1.x;
    int point1_end = point1_start + r1.width;
    int point2_start = r2.x;
    int point2_end = point2_start + r2.width;

    if (between(point1_start, point1_end, point2_start) &&
        between(point1_start, point1_end, point2_end)) {
      inter.point = point2_start;
      inter.length = point2_end - point2_start;
    }
    else if (between(point1_start, point1_end, point2_start)) {
      inter.point = point2_start;
      inter.length = point1_end - point2_start;
    }
    else if (between(point1_start, point1_end, point2_end)) {
      inter.point = point1_start;
      inter.length = point2_end - point1_start;
    }
    else {
      inter.point = 0;
      inter.length = -1;
    }
  }
  else {
    int point1_start = r1.y;
    int point1_end = point1_start + r1.height;
    int point2_start = r2.y;
    int point2_end = point2_start + r2.height;

    if (between(point1_start, point1_end, point2_start) &&
        between(point1_start, point1_end, point2_end)) {
      inter.point = point2_start;
      inter.length = point2_end - point2_start;
    }
    else if (between(point1_start, point1_end, point2_start)) {
      inter.point = point2_start;
      inter.length = point1_end - point2_start;
    }
    else if (between(point1_start, point1_end, point2_end)) {
      inter.point = point1_start;
      inter.length = point2_end - point1_start;
    }
    else {
      inter.point = 0;
      inter.length = -1;
    }
  }

  return inter;
}

rectangle intersection(rectangle r1, rectangle r2) {
  //WRITE THIS FUNCTION

  //Standard the rect
  r1 = canonicalize(r1);
  r2 = canonicalize(r2);

  //Check if there is a intersection between two rect's w
  line inter_w = cal_inter(r1, r2, 0);
  line inter_h = cal_inter(r1, r2, 1);

  rectangle intersection;
  intersection.x = inter_w.point;
  intersection.y = inter_h.point;
  intersection.width = inter_w.length;
  intersection.height = inter_h.length;

  if (intersection.width == -1 || intersection.height == -1) {
    intersection.width = 0;
    intersection.height = 0;
  }
  return intersection;
}

//You should not need to modify any code below this line
void printRectangle(rectangle r) {
  r = canonicalize(r);
  if (r.width == 0 && r.height == 0) {
    printf("<empty>\n");
  }
  else {
    printf("(%d,%d) to (%d,%d)\n", r.x, r.y, r.x + r.width, r.y + r.height);
  }
}

int main(void) {
  rectangle r1;
  rectangle r2;
  rectangle r3;
  rectangle r4;

  r1.x = 2;
  r1.y = 3;
  r1.width = 5;
  r1.height = 6;
  printf("r1 is ");
  printRectangle(r1);

  r2.x = 4;
  r2.y = 5;
  r2.width = -5;
  r2.height = -7;
  printf("r2 is ");
  printRectangle(r2);

  r3.x = -2;
  r3.y = 7;
  r3.width = 7;
  r3.height = -10;
  printf("r3 is ");
  printRectangle(r3);

  r4.x = 0;
  r4.y = 7;
  r4.width = -4;
  r4.height = 2;
  printf("r4 is ");
  printRectangle(r4);

  //test everything with r1
  rectangle i = intersection(r1, r1);
  printf("intersection(r1,r1): ");
  printRectangle(i);

  i = intersection(r1, r2);
  printf("intersection(r1,r2): ");
  printRectangle(i);

  i = intersection(r1, r3);
  printf("intersection(r1,r3): ");
  printRectangle(i);

  i = intersection(r1, r4);
  printf("intersection(r1,r4): ");
  printRectangle(i);

  //test everything with r2
  i = intersection(r2, r1);
  printf("intersection(r2,r1): ");
  printRectangle(i);

  i = intersection(r2, r2);
  printf("intersection(r2,r2): ");
  printRectangle(i);

  i = intersection(r2, r3);
  printf("intersection(r2,r3): ");
  printRectangle(i);

  i = intersection(r2, r4);
  printf("intersection(r2,r4): ");
  printRectangle(i);

  //test everything with r3
  i = intersection(r3, r1);
  printf("intersection(r3,r1): ");
  printRectangle(i);

  i = intersection(r3, r2);
  printf("intersection(r3,r2): ");
  printRectangle(i);

  i = intersection(r3, r3);
  printf("intersection(r3,r3): ");
  printRectangle(i);

  i = intersection(r3, r4);
  printf("intersection(r3,r4): ");
  printRectangle(i);

  //test everything with r4
  i = intersection(r4, r1);
  printf("intersection(r4,r1): ");
  printRectangle(i);

  i = intersection(r4, r2);
  printf("intersection(r4,r2): ");
  printRectangle(i);

  i = intersection(r4, r3);
  printf("intersection(r4,r3): ");
  printRectangle(i);

  i = intersection(r4, r4);
  printf("intersection(r4,r4): ");
  printRectangle(i);

  return EXIT_SUCCESS;
}
