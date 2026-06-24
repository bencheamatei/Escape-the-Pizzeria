//
// Created by matei on 6/22/2026.
//

#ifndef OOP_SCENE_MANAGER_H
#define OOP_SCENE_MANAGER_H

#include <memory>
#include <stack>
#include <scenes/scene.h>

class scene_manager {
private:
    std::stack<std::unique_ptr<scene>> d;
    int to_pop = 0;
    std::unique_ptr<scene> to_push = nullptr;

public:
    scene_manager() = default;

    void add_scene(std::unique_ptr<scene> scene);
    void rm_scene();
    void apply_lazy();

    void update(float dt);
    void render(sf::RenderWindow& window);
    void process_event(const sf::Event& event);

    void clear();

    // [[nodiscard]] bool is_empty() const;
};


#endif //OOP_SCENE_MANAGER_H