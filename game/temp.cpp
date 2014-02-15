#include <CoreFoundation/CoreFoundation.h>
#include <CoreGraphics/CoreGraphics.h>
#include <iostream>
using namespace std;

CGEventRef event = CGEventCreate(NULL);
CGPoint cursor = CGEventGetLocation(event);
CFRelease(event);

int main () {
  while (1) {
    cout << "H" << endl;
  }

  return 0;
}
