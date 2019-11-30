# SwallowEngine

**A Game engine based on the Hazel Engine by TheCherno**

The Swallow engine is coded in C++ and is intended to be a cross-platform high-performance game engine.



## Getting Started

** to get started clone this repository and all submodules.

Update the premake5.lua in the root of the repository to fit with your project. By default the premake5.lua is configured to compile the engine with a sandbox application.

** Visual Studio
Open the scripts directory in the root of the repository and run "WindowsGenerate.bat". Ths should create A .sln file in the root of your repository.

** Makefile On MACOS
Open the scripts directory in the root of the repository and run "MACOSGenerate.sh". Ths should create A makefile in the root of your repository.

### Prerequisites

No prerequisits apart from the submodules in the repository.

### Installing

For your application to run you must:

Create a class that inherits from Swallow::Application:

** sandboxApp.hpp
```
#pragma once
#include <Swallow.hpp>

class Sandbox : public Swallow::Application
{
public:
	Sandbox();
	virtual ~Sandbox();

private:
	Sandbox(const Sandbox &s) = default;
	Sandbox &operator=(const Sandbox &s) = default;
};

```

Create An instance of that class by overriding the application creation function:

** sanboxApp.cpp
```
#include "sandboxApp.hpp"

Sandbox::Sandbox() {
}

Sandbox::~Sandbox() {
}

Swallow::Application* Swallow::CreateApplication()
{
	return (new Sandbox());
}
```

This should run an application window with a black screen. For examples on how to expand this applications funtioanality look into the layer system usage in the sandbox app.

## Built With

* [C++](https://devdocs.io/cpp/) - The base language
* [OpenGL](https://www.opengl.org/documentation/) - Used for rendering
* [GLM](https://glm.g-truc.net/0.9.8/index.html) - Used for maths functions
* [ImGUI](https://rometools.github.io/rome/) - Used for debugging Gui elements

## Contributing

Please read [CONTRIBUTING.md](https://gist.github.com/PurpleBooth/b24679402957c63ec426) for details on our code of conduct, and the process for submitting pull requests to us.

## Versioning

We use [SemVer](http://semver.org/) for versioning. For the versions available, see the [tags on this repository](https://github.com/your/project/tags). 

## Authors

* **Isard Botha** - *Initial work* - [Ibotha](https://github.com/ibotha)

See also the list of [contributors](https://github.com/ibotha/SwallowEngine/contributors) who participated in this project.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Again. Thank you to TheCherno for sharing what he knows and giving me the understanding to build something like this.
