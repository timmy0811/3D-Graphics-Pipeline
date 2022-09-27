#include "GUI.h"

projection::GUI::GUI(ObjectHandler* objHandler)
{
    m_Sprite = nullptr;
    m_Handler = objHandler;

    m_Objects = *objHandler->getObjects();
    m_Textures = objHandler->getTextures();

    /*for (int i = 0; i < textures->size(); i++) {
        textureItems[i] = (*textures)[i]->getName().c_str();
    }*/
}

void projection::GUI::menuBar() const
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

void projection::GUI::objectBrowser() const
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

            for (int i = 0; i < m_Objects.size(); i++)
            {
                ImGuiTreeNodeFlags node_flags;
                if (m_Objects[i]->getChildren().size()) {
                    node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                }
                else {
                    node_flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                }

                bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, m_Objects[i]->getName().c_str());

                treeChildren(node_flags, node_open, m_Objects[i]);

            }
            ImGui::TreePop();
            ImGui::PopStyleVar();
        }
    }
    ImGui::End();
}

void projection::GUI::treeChildren(ImGuiTreeNodeFlags node_flags, bool isOpen, AbstractObject* obj) const
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

void projection::GUI::objectAttributes()
{
    ImGui::SetNextWindowSize(ImVec2(c_objectAttrWidth, c_objectAttrHeight));
    ImGui::SetNextWindowPos(ImVec2(c_winWidth - c_objectAttrWidth - c_Padding, c_PaddingTop));
    AbstractObject* obj = m_Handler->getActiveObj();

    if (obj) {
        ImGui::Begin(("Object Attributes - " + obj->getName()).c_str());

        if (m_Name != obj->getName()) {
            update(obj);
        }

        if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)) {

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Position   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XT", &(m_Position.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YT", &(m_Position.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZT", &(m_Position.z));
            
            ImGui::SetNextItemWidth(200.f);
            ImGui::Text("Rotation   ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XR", &(m_Rotation.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YR", &(m_Rotation.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZR", &(m_Rotation.z));

            ImGui::SetNextItemWidth(100.f);
            ImGui::Text("Scale      ");

            // X
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("XS", &(m_Scale.x));
            // Y
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("YS", &(m_Scale.y));
            // Z
            ImGui::SameLine();
            ImGui::SetNextItemWidth(80.f);
            ImGui::InputFloat("ZS", &(m_Scale.z));

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
            if (m_Name != obj->getName() || !m_Sprite) {
                //update(obj);
                if (m_Sprite) {
                    delete m_Sprite->getTexture();
                    delete m_Sprite;
                }
                m_Sprite = texPtr->getTexture()->getSpriteObject();
                if (m_Sprite) {
                    float fx = 150.f / m_Sprite->getTexture()->getSize().x;
                    float fy = 150.f / m_Sprite->getTexture()->getSize().y;
                    m_Sprite->setScale(sf::Vector2f(fx, fy));
                    //currentItem = texPtr->getTexture()->getName().c_str();
                }
            }
            if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen) && m_Sprite) {
                ImGui::Image(*m_Sprite);
                ImGui::SameLine();
                //ImGui::Text(std::to_string(static_cast<Textured*>(obj)->getTexture()->getType()));
                ImGui::SameLine();

                ImGui::BeginChild(1);
                ImGui::Text(("Name: " + texPtr->getTexture()->getName()).c_str());
                ImGui::Text(("Resolution: " + std::to_string(m_Sprite->getTexture()->getSize().x) + "px / " + std::to_string(m_Sprite->getTexture()->getSize().y) + "px").c_str());
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

void projection::GUI::diagnosticsWindow(sf::Vector3f* cameraPos, int fps) const
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

void projection::GUI::update(AbstractObject* obj)
{
    m_Position = *obj->getPositionAbs();
    m_Scale = *obj->getScaleAbs();
    m_Rotation = *obj->getRotationAbs();

    m_Name = obj->getName();
}

void projection::GUI::apply(AbstractObject* obj) const
{
    obj->setName(m_Name);

    obj->moveToPos(m_Position);
    obj->setPostion(m_Position);

    obj->setRotation(m_Rotation);

    obj->setScale(m_Scale);
}

void projection::GUI::updateBrowser()
{
    //objects = *Handler->getObjects();
}
