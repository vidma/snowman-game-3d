#ifndef INC_SNAPSHOT_H
#define INC_SNAPSHOT_H

#include <vector>

class SnapShot {
public:
  SnapShot();
  SnapShot(int w,int h);
  void shot();
  void shotIfRequested();
  void request();
  void resize(int w,int h);
  ~SnapShot();
private:
  void init();
  bool requested;
  std::vector<unsigned char> pixel;
  int num;
  int width,height;
  int numgif;
  unsigned int imgId;
};

#endif
