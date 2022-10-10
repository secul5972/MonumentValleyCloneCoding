# MonumentValleyCloneCoding
please see the documentmentation
# 혹시 안된다면
프로젝트 속성 -> 디버그 -> 환경에 PATH=$(SolutionDir)$(SolutionName)\lib;%PATH%

//아래는 적용 되어있음 시작 $뒤 공백은 지우고 넣기

c/c++ -> 일반 -> 추가 포함 디렉터리 $ (SolutionDir)$(SolutionName)\include

링커 -> 일반 -> 추가 라이브러리 디렉터리 $ (SolutionDir)$(SolutionName)\lib

링커 -> 입력 -> 추가 종속성 glfw3.lib;opengl32.lib;
