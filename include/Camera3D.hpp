#ifndef RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
#define RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_

#include "./raylib.hpp"
#include "./Vector3.hpp"
#include "./raylib-cpp-utils.hpp"

namespace raylib {
/**
 * Camera type, defines a camera position/orientation in 3d space
 */
class Camera3D : public ::Camera3D {
 public:
    Camera3D(const ::Camera3D& camera) {
        set(camera);
    }

    /**
     * Create a new Camera3D.
     *
     * @param position Camera position
     * @param target Camera target it looks-at
     * @param up Camera up vector (rotation over its axis)
     * @param fovy Camera field-of-view apperture in Y (degrees) in perspective, used as near plane width in orthographic
     * @param projection Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
     */
    Camera3D(::Vector3 position,
            ::Vector3 target = ::Vector3{0.0f, 0.0f, 0.0f},
            ::Vector3 up = ::Vector3{0.0f, 1.0f, 0.0f},
            float fovy = 0,
            int projection = CAMERA_PERSPECTIVE) : ::Camera3D{position, target, up, fovy, projection} {}

    Camera3D() {}

    GETTERSETTER(::Vector3, Position, position)
    GETTERSETTER(::Vector3, Target, target)
    GETTERSETTER(::Vector3, Up, up)
    GETTERSETTER(float, Fovy, fovy)
    GETTERSETTER(int, Projection, projection)

    Camera3D& operator=(const ::Camera3D& camera) {
        set(camera);
        return *this;
    }

    /**
     * Initializes 3D mode with custom camera (3D)
     */
    Camera3D& BeginMode() {
        ::BeginMode3D(*this);
        return *this;
    }

    /**
     * Ends 3D mode and returns to default 2D orthographic mode
     */
    Camera3D& EndMode() {
        ::EndMode3D();
        return *this;
    }

    /**
     * Get transform matrix for camera
     */
    inline Matrix GetMatrix() const {
        return ::GetCameraMatrix(*this);
    }

    /**
     * Set camera mode (multiple camera modes available)
     */
    inline Camera3D& SetMode(int mode) {
        ::SetCameraMode(*this, mode);
        return *this;
    }

    /**
     * Set camera alt key to combine with mouse movement (free camera)
     */
    inline Camera3D& SetAltControl(int altKey) {
        ::SetCameraAltControl(altKey);
        return *this;
    }

    /**
     * Set camera smooth zoom key to combine with mouse (free camera)
     */
    inline Camera3D& SetSmoothZoomControl(int szKey) {
        ::SetCameraSmoothZoomControl(szKey);
        return *this;
    }

    /**
     * Set camera move controls (1st person and 3rd person cameras)
     */
    inline Camera3D& SetMoveControls(
            int frontKey, int backKey,
            int rightKey, int leftKey,
            int upKey, int downKey) {
        ::SetCameraMoveControls(frontKey, backKey, rightKey, leftKey, upKey, downKey);
        return *this;
    }

    /**
     * Update camera position for selected mode
     */
    inline Camera3D& Update() {
        ::UpdateCamera(this);
        return *this;
    }

    /**
     * Returns a ray trace from mouse position
     */
    inline Ray GetMouseRay(::Vector2 mousePosition) const {
        return ::GetMouseRay(mousePosition, *this);
    }

    /**
     * Returns the screen space position for a 3d world space position
     */
    inline Vector2 GetWorldToScreen(::Vector3 position) const {
        return ::GetWorldToScreen(position, *this);
    }

    /**
     * Draw a billboard texture.
     */
    inline Camera3D& DrawBillboard(
            const ::Texture2D& texture,
            ::Vector3 center,
            float size,
            ::Color tint = {255, 255, 255, 255}) {
        ::DrawBillboard(*this, texture, center, size, tint);
        return *this;
    }

    /**
     * Draw a billboard texture defined by source.
     */
    inline Camera3D& DrawBillboard(
            const ::Texture2D& texture,
            ::Rectangle sourceRec,
            ::Vector3 center,
            ::Vector2 size,
            ::Color tint = {255, 255, 255, 255}) {
        ::DrawBillboardRec(*this, texture, sourceRec, center, size, tint);
        return *this;
    }

 private:
    void set(const ::Camera3D& camera) {
        position = camera.position;
        target = camera.target;
        up = camera.up;
        fovy = camera.fovy;
        projection = camera.projection;
    }
};

typedef Camera3D Camera;
}  // namespace raylib
using RCamera = raylib::Camera;
using RCamera3D = raylib::Camera3D;

#endif  // RAYLIB_CPP_INCLUDE_CAMERA3D_HPP_
