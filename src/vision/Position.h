#ifndef POSITION_H
#define POSITION_H

/**
 * @brief 클래스 로드를 위한 예시용 Position 클래스
 */
class Position
{
public:
  Position() : x(0), y(0) {}

  Position(double x, double y) : x(x), y(y) {}

  double getX() const { return x; }
  double getY() const { return y; }

  void setX(double x) { this->x = x; }
  void setY(double y) { this->y = y; }

  bool isValid() const
  {
    // 추가 검증 로직을 필요에 따라 추가
    return x >= 0 && y >= 0;
  }

  double x;
  double y;
};

#endif // POSITION_H