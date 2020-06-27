#ifndef TESTING_LAYER_H
#define TESTING_LAYER_H

#include "Hazel.h"

class TestingLayer : public Hazel::Layer
{
public:
    TestingLayer();
    virtual ~TestingLayer() = default;

    void OnAttach() override;
    void OnDetach() override;

    void OnUpdate(Hazel::Timestep ts) override;
    void OnImGuiRender() override;
    void OnEvent(Hazel::Event& e) override;
};


#endif /* TESTING_LAYER_H */


