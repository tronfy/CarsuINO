#include "Carsu.h"

String Carsu::package(String gas, float ppm)
{
  String strData = gas;
  strData.concat("|");
  strData.concat(ppm);

  String pkg = "<" + String(strData) + ">";
  return pkg;
}
