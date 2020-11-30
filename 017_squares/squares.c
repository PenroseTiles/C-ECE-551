#define AND &&
#define OR ||
#define max(x, y) x > y ? x : y

void squares(int size1, int x_offset, int y_offset, int size2) {
  //compute the max of size1 and (x_offset + size2).  Call this w
  int w = max(size1, x_offset + size2);
  //compute the max of size1 and (y_offset + size2).  Call this h
  int h = max(size1, y_offset + size2);
  //count from 0 to h. Call the number you count with y
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      //count from 0 to w. Call the number you count with x
      if ((x_offset <= x AND x <
           x_offset + size2 AND(y == y_offset OR y == y_offset + size2 - 1))
              OR(y_offset <= y AND y <
                 y_offset + size2 AND(x == x_offset OR x == x_offset + size2 - 1))) {
        putchar('*');
        //check if  EITHER
        //    ((x is between x_offset  and x_offset +size2) AND
        //     y is equal to either y_offset OR y_offset + size2 - 1 )
        //  OR
        //    ((y is between y_offset and y_offset + size2) AND
        //     x is equal to either x_offset OR x_offset + size2 -1)
        // if so, print a *
      }
      else if ((x < size1 AND(y == 0 OR y == size1 - 1))
                   OR(y < size1 AND(x == 0 OR x == size1 - 1))) {
        putchar('#');
      }
      else {
        putchar(' ');
      }
    }
    printf("\n");
    //if not,
    // check if EITHER
    //    x is less than size1 AND (y is either 0 or size1-1)
    // OR
    //    y is less than size1 AND (x is either 0 or size1-1)
    //if so, print a #
  }
  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
