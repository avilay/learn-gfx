#include <stdio.h>
#include <box2d.h>

int main(void) {
  b2WorldDef world_def = b2DefaultWorldDef();
  world_def.gravity = (b2Vec2){.x=0.0f, .y=-10.0f};
  b2WorldId world_id = b2CreateWorld(&world_def);

  b2BodyDef ground_body_def = b2DefaultBodyDef();
  ground_body_def.position = (b2Vec2){.x=0.0f, .y=-10.0f};
  b2BodyId ground_id = b2CreateBody(world_id, &ground_body_def);

  b2Polygon ground_box = b2MakeBox(50.0f, 10.0f);
  b2ShapeDef ground_shape_def = b2DefaultShapeDef();
  b2CreatePolygonShape(ground_id, &ground_shape_def, &ground_box);

  b2BodyDef body_def = b2DefaultBodyDef();
  body_def.type = b2_dynamicBody;
  body_def.position = (b2Vec2){.x=0.0f, .y=4.0f};
  b2BodyId body_id = b2CreateBody(world_id, &body_def);

  b2Polygon dynamic_box = b2MakeBox(1.0f, 1.0f);
  b2ShapeDef shape_def = b2DefaultShapeDef();
  shape_def.density = 1.0f;
  shape_def.friction = 0.3f;
  b2CreatePolygonShape(body_id, &shape_def, &dynamic_box);

  float time_step = 1.0f/60.0f;
  int sub_step_count = 4;
  for (int i = 0; i < 90; i++) {
    b2World_Step(world_id, time_step, sub_step_count);
    b2Vec2 position = b2Body_GetPosition(body_id);
    b2Rot rotation = b2Body_GetRotation(body_id);
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, b2Rot_GetAngle(rotation));
  }

  b2DestroyWorld(world_id);
  return 0;
}