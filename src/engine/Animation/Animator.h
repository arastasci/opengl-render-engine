#pragma once
#include <vector>
#include "Animation.h"
class Animator
{
public:
    Animator(Animation* Animation);
    Animator() = default;
    void UpdateAnimation(float dt);

    void PlayAnimation(Animation* pAnimation);

    void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
   
    std::vector<glm::mat4> GetFinalBoneMatrices() const;

private:
    std::vector<glm::mat4> m_FinalBoneMatrices;
    Animation* m_CurrentAnimation;
    float m_CurrentTime;
    float m_DeltaTime;
};
