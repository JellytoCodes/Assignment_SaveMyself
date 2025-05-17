# 📝 SaveMyself Project TroubleShooting History
**1인 게임 개발 프로젝트를 진행하면서 문제 해결 과정을 기록하고자 만든 기록물입니다.**

<br>

## 📌 CASE 1 : 창고 진입 시 간헐적 크래시 발생 및 버튼 클릭 횟수 증가 (2025.05)  
**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;→ 창고 진입 시 간헐적 크래시 발생 (0x0000000 nullptr 에러로 의심)  
&nbsp;&nbsp;&nbsp;→ 창고 진입/탈출 이후 재진입 시 버튼 클릭량이 증가하는 현상 발견  

**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;→ Overlap에서 UI를 생성하고 파괴하는 과정에서 발견된 문제로 파악  
   
**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;→ 게임 시작 시 Widget 생성  
&nbsp;&nbsp;&nbsp;→ ESlateVisibility::Visible, ESlateVisibility::Collapsed으로 UI 출력 관리하는 것으로 변경  

**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;→ UI를 반드시 지우는것만 최적화가 아닌 버그 발현도 고려하며 고정적으로 사용되는 UI는 ESlateVisibility로 제어할 수 있도록 설계 고려  
