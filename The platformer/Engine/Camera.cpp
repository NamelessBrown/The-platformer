#include "Camera.h"
#include "Engine.h"

Camera* Camera::s_instance = nullptr;

Camera* Camera::GetInstance()
{
    if (s_instance == nullptr)
    {
        s_instance = new Camera();
    }

    return s_instance;
}

Camera::Camera()
{
    m_position = sf::Vector2f(0.f, 0.f);
    m_viewBox.left = 0;
    m_viewBox.top = 0;
    m_viewBox.width = (int)Engine::GetInstance()->GetWindowWidth();
    m_viewBox.height = (int)Engine::GetInstance()->GetWindowHeight();
    m_target = Point();
}

Camera::~Camera()
{

}

const sf::Vector2f& Camera::GetPosition() const
{
    return m_position;
}

const sf::IntRect& Camera::GetViewBox() const
{
    return m_viewBox;
}

void Camera::Quit()
{
    delete s_instance;
}

void Camera::SetTarget(const Point& target)
{
    m_target = target;
}

void Camera::Update(const float dt)
{
    m_viewBox.left = (int)m_target.x - Engine::GetInstance()->GetWindowWidth() / 2;
    m_viewBox.top = (int)m_target.y - Engine::GetInstance()->GetWindowHeight() / 2;

    if (m_viewBox.left < 0)
    {
        m_viewBox.left = 0;
    }
    if (m_viewBox.top < 0)
    {
        m_viewBox.top = 0;
    }

    if (m_viewBox.left > (2 * (int)Engine::GetInstance()->GetWindowWidth() - m_viewBox.width))
    {
        m_viewBox.left = (2 * (int)Engine::GetInstance()->GetWindowWidth() - m_viewBox.width);
    }

    if (m_viewBox.top > ((int)Engine::GetInstance()->GetWindowHeight() - m_viewBox.height))
    {
        m_viewBox.top = ((int)Engine::GetInstance()->GetWindowHeight() - m_viewBox.height);
    }

    m_position = sf::Vector2f((float)m_viewBox.left, (float)m_viewBox.top);
}
