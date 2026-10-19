
#ifndef COLLISION_AVOIDANCE_HPP
#define COLLISION_AVOIDANCE_HPP

#include <vector>

// ============================================================
// 1. 드론 상태 정보
// ============================================================
// 모든 위치와 속도는 동일한 NED 좌표계를 사용한다고 가정
// NED: 북쪽(N), 동쪽(E), 아래쪽(D)
// ============================================================

struct DroneState {
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;

    double vx = 0.0;
    double vy = 0.0;
    double vz = 0.0;
};

// ============================================================
// 2. 3차원 속도 정보
// ============================================================

struct Velocity3D {
    double vx = 0.0;
    double vy = 0.0;
    double vz = 0.0;
};

// ============================================================
// 3. 충돌 회피 제어기
// ============================================================

class CollisionAvoidance {
public:
    CollisionAvoidance();

    // 주변 드론과의 최소 안전거리 설정
    void set_safe_distance(double distance);

    // 기본 편대 속도를 입력받아 안전 속도 계산
    Velocity3D compute_safe_velocity(
        const DroneState& own_state,
        const std::vector<DroneState>& neighbors,
        const Velocity3D& desired_velocity
    );

private:
    double safe_distance_;
};

#endif
