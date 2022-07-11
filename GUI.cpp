#include "GUI.h"

void GUI::menuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New"))
            {
                //Do something
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Window"))
            {
                //Do something
            }
            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}

void GUI::objectBrowser(std::vector<AbstractObject*> objects)
{
    ImGui::SetNextWindowSize(ImVec2(c_objectBrowserWidth, c_objectBrowserHeight));
    ImGui::SetNextWindowPos(ImVec2(c_Padding, c_PaddingTop));
    ImGui::SetNextItemOpen(true);

    if (ImGui::Begin("Object Browser"))
    {
        //show a list of game objects
        ImGui::LabelText("", "UntitledScene*");
        ImGui::Separator();
        ImGui::SetNextItemOpen(true);

        if (ImGui::TreeNode("Object List"))
        {
            ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);

            for (int i = 0; i < objects.size(); i++)
            {
                ImGuiTreeNodeFlags node_flags;
                if (objects[i]->getChildren().size()) {
                    node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                }
                else {
                    node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                }

                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, objects[i]->getName().c_str());

                treeChildren(node_flags, node_open, objects[i]);

            }
            ImGui::TreePop();
            ImGui::PopStyleVar();
        }
    }
    ImGui::End();
}

void GUI::treeChildren(ImGuiTreeNodeFlags node_flags, bool isOpen, AbstractObject* obj)
{
    if (isOpen)
    {
        std::vector<AbstractObject*> children = obj->getChildren();
        for (int i = 0; i < children.size(); i++)
        {
            if (children[i]->getChildren().size() == 0)
            {
                node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
                ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, children[i]->getName().c_str());
            }
            else 
            {
                bool o = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "test");
                ImGui::TreePop();
                treeChildren(node_flags, o, obj);
            }
        }
        ImGui::TreePop();
    }
}

void GUI::objectAttributes(AbstractObject* obj)
{
    ImGui::SetNextWindowSize(ImVec2(c_objectAttrWidth, c_objectAttrHeight));
    ImGui::SetNextWindowPos(ImVec2(c_winWidth - c_objectAttrWidth - c_Padding, c_PaddingTop));

    ImGui::Begin("Object Attributes");

    if (obj) {
        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Position   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XT", &(obj->getPosition()->x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YT", &(obj->getPosition()->y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZT", &(obj->getPosition()->z));
            
            ImGui::SetNextItemWidth(200.f);
            ImGui::Text("Rotation   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XR", &(obj->getRotation()->x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YR", &(obj->getRotation()->y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZR", &(obj->getRotation()->z));

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Scale      ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XS", &(obj->getScale()->x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YS", &(obj->getScale()->y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZS", &(obj->getScale()->z));
        }
    }
    else {
        ImGui::Text("Select an object first");
    }

    ImGui::End();
}

void GUI::diagnosticsWindow(sf::Vector3f* cameraPos, int fps)
{
    ImGui::SetNextWindowSize(ImVec2(c_diagnosticsWidth, c_diagnosticsHeight));
    ImGui::SetNextWindowPos(ImVec2(c_winWidth - c_objectAttrWidth - 2 * c_Padding - c_diagnosticsWidth, c_PaddingTop));

    ImGui::Begin("Diagnostics");

    ImGui::Text("Camera:   ");
    ImGui::SameLine();
    ImGui::Text((std::to_string(-cameraPos->x)).c_str());
    ImGui::SameLine();
    ImGui::Text((std::to_string(-cameraPos->y)).c_str());
    ImGui::SameLine();
    ImGui::Text((std::to_string(-cameraPos->z)).c_str());

    ImGui::Text("FPS:      ");
    ImGui::SameLine();
    ImGui::Text((std::to_string(fps)).c_str());

    ImGui::End();
}
