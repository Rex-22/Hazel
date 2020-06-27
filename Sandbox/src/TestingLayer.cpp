#include "TestingLayer.h"

using namespace Hazel;

TestingLayer::TestingLayer()
{
}

void TestingLayer::OnAttach()
{
}

void TestingLayer::OnDetach()
{
}

void TestingLayer::OnUpdate(Hazel::Timestep ts)
{
    if(Io::WriteToFile("assets/Test.txt", "Hello there!", true))
    {
        HZ_INFO("Wrote file!");
    }
    
    auto fileData = Io::LoadFile("assets/Test.txt");
    HZ_INFO("File ({0:d} bytes):\n{1}", fileData.Size, fileData.Data);
}

void TestingLayer::OnImGuiRender()
{
}

void TestingLayer::OnEvent(Hazel::Event& e)
{
}
