scene scene_;
point *point_scene;

#define WIDTH 1000
#define HEIGHT 1000

void init_scene(scene* scene_to_set){
	scene_to_set->width=WIDTH;
	scene_to_set->height=HEIGHT;
	scene_to_set->shiftX=0;
	scene_to_set->shiftY=0;

	scene_to_set->distance=100;

	scene_to_set->P.x=0;
	scene_to_set->P.y=0;
	scene_to_set->P.z=scene_to_set->distance;

	scene_to_set->Pabs.x=0;
	scene_to_set->Pabs.y=0;
	scene_to_set->Pabs.z=0;

	scene_to_set->X.x=1;
	scene_to_set->X.y=0;
	scene_to_set->X.z=0;

	scene_to_set->Y.x=0;
	scene_to_set->Y.y=1;
	scene_to_set->Y.z=0;

	scene_to_set->Z.x=0;
	scene_to_set->Z.y=0;
	scene_to_set->Z.z=1;

	scene_to_set->focus.x=0;
	scene_to_set->focus.y=0;
	scene_to_set->focus.z=40;

	scene_to_set->alpha=0;
	scene_to_set->sigma=0;

	scene_to_set->points=point_scene=point_new();
}

