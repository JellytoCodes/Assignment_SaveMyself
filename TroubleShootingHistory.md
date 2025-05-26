# 📝 SaveMyself Project TroubleShooting History
**1인 게임 개발 프로젝트를 진행하면서 문제 해결 과정을 기록하고자 만든 기록물입니다.**

<br>

## 📌 CASE 1 : 창고 진입 시 간헐적 크래시 발생 및 버튼 클릭 횟수 증가 (2025.05)  
&nbsp;**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;&nbsp; → 창고 진입 시 간헐적 크래시 발생 (0x0000000 nullptr 에러로 의심)  
&nbsp;&nbsp;&nbsp;&nbsp; → 창고 진입/탈출 이후 재진입 시 버튼 클릭량이 증가하는 현상 발견  

&nbsp;**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;&nbsp; → Overlap에서 UI를 생성하고 파괴하는 과정에서 발견된 문제로 파악  
   
&nbsp;**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → 게임 시작 시 Widget 생성  
&nbsp;&nbsp;&nbsp;&nbsp; → ESlateVisibility::Visible, ESlateVisibility::Collapsed으로 UI 출력 관리하는 것으로 변경  

&nbsp;**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → UI를 반드시 지우는것만 최적화가 아닌 버그 발현도 고려하며 고정적으로 사용되는 UI는 ESlateVisibility로 제어할 수 있도록 설계 고려  

<br>

## 📌 CASE 2 : QuickSlotWrapBox가 nullptr로 바뀌는 문제 (2025.05)  
&nbsp;**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;&nbsp; → AddItemQuickSlot() 호출 시점에서 QuickSlotWrapBox == nullptr 발생  
&nbsp;&nbsp;&nbsp;&nbsp; → PIE 첫 실행 시 정상이나 창고에서 Button 클릭 시 nullptr로 접근  

&nbsp;**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;&nbsp; → Delegate 바인딩 위치 문제에 따른 오류  
&nbsp;&nbsp;&nbsp;&nbsp; → 출력은 DefenseCharacter에서 담당하나 Delegate 바인딩은 StorageWidget에서 수신  

&nbsp;**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → Delegate 바인딩 구조 변경  
&nbsp;&nbsp;&nbsp;&nbsp; → DefenseCharacter에서 QuickSlot에 Item을 추가하는 함수 및 해당 함수를 Delegate에 바인딩하는 함수를 추가  
&nbsp;&nbsp;&nbsp;&nbsp; → 최종적으로 StorageSlot→Player→QuickSlotWidget으로 구조 변경  

&nbsp;**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → Delegate를 등록하는 클래스와 출력되는 UI 인스턴스를 관리하는 클래스는 반드시 동일한 인스턴스 기반에서 연결될 수 있도록 설계  

<br>

## 📌 CASE 3 : 구조물 설치 시스템 문제 통합 정리 (2025.05) 
&nbsp;**⚠️ 문제 상황**  
&nbsp;&nbsp;&nbsp;&nbsp; 1) 구조물이 땅에 파묻히는 문제  
&nbsp;&nbsp;&nbsp;&nbsp; 2) 설치 불가 위치에서도 설치가 가능한 문제  
&nbsp;&nbsp;&nbsp;&nbsp; 3) 설치 불가 상태에서도 설치가 강제로 실행되는 문제  

&nbsp;**🔍 원인 분석**  
&nbsp;&nbsp;&nbsp;&nbsp; 1) StaticMesh의 Z축 보정 미적용  
&nbsp;&nbsp;&nbsp;&nbsp; 2-1) Overlap검사 대상이 PlayerItem으로 한정되어있어 다른 구조물들이 검사 대상에서 제외  
&nbsp;&nbsp;&nbsp;&nbsp; 2-2) PlacementCheckBox에 사이즈 설정이 없어 Overlap 감지 범위가 작아 발생한 오류  
&nbsp;&nbsp;&nbsp;&nbsp; 3) PreviewInstance = nullptr; 코드로 인하여 마우스 클릭 시 TrowWeapon()이 호출된 문제  

&nbsp;**🛠️ 해결 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; 1) Bounds.BoxExtent.Z만큼 Z축 보정하여 위치 계산 적용  
&nbsp;&nbsp;&nbsp;&nbsp; 2) GetOverlappingActors() 클래스 필터 제거 및 SetBoxExtent() 감지 범위 확대  
&nbsp;&nbsp;&nbsp;&nbsp; 3) PreviewInstance = nullptr; 삭제 및 설치 가능 여부 체크 후 수량 감소  

&nbsp;**📈 개선 방안**  
&nbsp;&nbsp;&nbsp;&nbsp; → 설치 위치 판단은 시각 피드백과 실제 논리 판정이 일치할 수 있도록 설계  
&nbsp;&nbsp;&nbsp;&nbsp; → 수량 / 상태 기반 설치 불가 처리시 조건 검증 구조를 고려하여 설계
