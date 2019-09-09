#pragma once

namespace Swallow {

	class Primatives
	{
	public:
		Primatives();
		Primatives(const Primatives&);
        Primatives &operator=(const Primatives&);
        ~Primatives();

        static Ref<GameObject> Cube();
        static Ref<GameObject> Quad();
    };
}