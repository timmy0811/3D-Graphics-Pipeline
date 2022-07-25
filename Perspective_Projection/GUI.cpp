#include "GUI.h"

GUI::GUI(ObjectHandler* objHandler)
{
    sprt = nullptr;
    Handler = objHandler;

    objects = *objHandler->getObjects();
    textures = objHandler->getTextures();

    /*for (int i = 0; i < textures->size(); i++) {
        textureItems[i] = (*textures)[i]->getName().c_str();
    }*/
}

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

void GUI::objectBrowser()
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

void GUI::objectAttributes()
{
    ImGui::SetNextWindowSize(ImVec2(c_objectAttrWidth, c_objectAttrHeight));
    ImGui::SetNextWindowPos(ImVec2(c_winWidth - c_objectAttrWidth - c_Padding, c_PaddingTop));
    AbstractObject* obj = Handler->getActiveObj();

    if (obj) {
        ImGui::Begin(("Object Attributes - " + obj->getName()).c_str());

        if (name != obj->getName()) {
            update(obj);
        }

        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Position   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XT", &(position.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YT", &(position.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZT", &(position.z));
            
            ImGui::SetNextItemWidth(200.f);
            ImGui::Text("Rotation   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XR", &(rotation.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YR", &(rotation.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZR", &(rotation.z));

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Scale      ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XS", &(scale.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YS", &(scale.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZS", &(scale.z));

            ImGui::Separator();

            // Buttons
            if (ImGui::Button("Update", ImVec2(195.f, 22.f))) {
                update(obj);
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(120.f);
            if (ImGui::Button("Apply", ImVec2(195.f, 22.f))) {
                apply(obj);
            }
        }
        if (dynamic_cast<Textured*>(obj) != nullptr && dynamic_cast<Textured*>(obj)->isTextured) {
            Textured* texPtr = static_cast<Textured*>(obj);
            if (name != obj->getName() || !sprt) {
                //update(obj);
                if (sprt) {
                    delete sprt->getTexture();
                    delete sprt;
                }
                sprt = texPtr->getTexture()->getSpriteObject();
                if (sprt) {
                    float fx = 150.f / sprt->getTexture()->getSize().x;
                    float fy = 150.f / sprt->getTexture()->getSize().y;
                    sprt->setScale(sf::Vector2f(fx, fy));
                    //currentItem = texPtr->getTexture()->getName().c_str();
                }
            }
            if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen) && sprt) {
                ImGui::Image(*sprt);
                ImGui::SameLine();
                //ImGui::Text(std::to_string(static_cast<Textured*>(obj)->getTexture()->getType()));
                ImGui::SameLine();

                ImGui::BeginChild(1);
                ImGui::Text(("Name: " + texPtr->getTexture()->getName()).c_str());
                ImGui::Text(("Resolution: " + std::to_string(sprt->getTexture()->getSize().x) + "px / " + std::to_string(sprt->getTexture()->getSize().y) + "px").c_str());
                ImGui::EndChild();

                //ImGui::BeginCombo("test A", "test B");
                ////ImGui::Combo("test Item", 0, "");
                //ImGui::EndCombo();
            }
            else {
                ImGui::Text("No Texture set");
            }
        }
    }
    else {
        ImGui::Begin("Object Attributes");
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

void GUI::update(AbstractObject* obj)
{
    position = *obj->getPositionAbs();
    scale = *obj->getScaleAbs();
    rotation = *obj->getRotationAbs();

    name = obj->getName();
}

void GUI::apply(AbstractObject* obj)
{
    obj->setName(name);

    obj->moveToPos(position);
    obj->setPostion(position);

    obj->setRotation(rotation);

    obj->setScale(scale);
}
