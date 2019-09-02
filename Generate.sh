./vendor/bin/premake/premake5 gmake2

mkdir -p ./Swallow/vendor/AssImp/build && cd ./Swallow/vendor/AssImp/build && cmake .. -G 'Unix Makefiles' && make