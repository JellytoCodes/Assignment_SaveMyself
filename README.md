# 🛡️ SaveMyself [2025 1학년 1학기 기말과제 프로젝트]  
본 프로젝트는 언리얼 엔진 5.4.4를 기반으로 제작된 **싱글 플레이어 디펜스 생존 게임**입니다.

## 프로젝트 개요
 **플레이어가 직접 컨트롤하는 디펜스를 만들어보고 싶다**라는 틀을 메인으로 시작한 프로젝트입니다.  
 매 스테이지마다 플레이어는 필요한 아이템을 구매하고 구조물 및 함정을 설치하는 등의 행동으로 전략을 구성하여 시간 내 적을 모두 물리치는 것이 게임의 진행 흐름입니다.  

## 게임 컨셉
 플레이어는 한 나라에서 유일하게 살아남은 생존자이며 적과 싸워 끝까지 살아남겠다는 의지를 갖고 나아가는 것이 목표이자 삶의 희망이다.
 
<br>

## ⚔️ 게임 시스템
&nbsp;&nbsp;&nbsp;**🎒 인벤토리 시스템**  
&nbsp;&nbsp;&nbsp;**🏪 상점(물자 창고) 시스템**  
&nbsp;&nbsp;&nbsp;&nbsp;→ 가방(적재량 기반) 기능을 도입하여 상점에서 구매 시 각 아이템에 대한 무게를 고려하여 플레이어가 인벤토리에 담을 수 있도록 설계

## ⚙️ AI & 전투 시스템
&nbsp;&nbsp;&nbsp;**🧱 구조물 및 함정 시스템**  
&nbsp;&nbsp;&nbsp;**👾 몬스터 AI**  
&nbsp;&nbsp;&nbsp;**🗺️ 스테이지 진행 구조**  
&nbsp;&nbsp;&nbsp;**📊 Result 시스템**  
&nbsp;&nbsp;&nbsp;&nbsp;→ 몬스터는 Perception Sight 기반으로 탐색하며 FMS 기반 구조로 플레이어에게 접근하는 방식으로 설계  
&nbsp;&nbsp;&nbsp;&nbsp;→ 구조물 및 함정은 Overlap을 활용하여 몬스터가 구조물을 공격하고 함정을 밟아 발동하는 방식으로 설계  
&nbsp;&nbsp;&nbsp;&nbsp;→ 방어 성공/실패 여부에 따라 Next Stage / Retry 로 분기되며 각 상황에 맞게 UI가 출력되도록 설계  

## 🛠️ 기타 시스템
&nbsp;&nbsp;&nbsp;**💾 저장 / 불러오기 시스템**  
&nbsp;&nbsp;&nbsp;&nbsp;→ 언리얼 엔진 내 지원하는 SaveGame Class를 활용하여 설계  
<br> 

## 🧠 시스템 설계 개요
&nbsp;&nbsp;&nbsp;→ Delegate 및 Event 기반 통신 구조  
&nbsp;&nbsp;&nbsp;→ Subsystem 분리 구조 적용 (아이템 데이터, 세이브 등)  
&nbsp;&nbsp;&nbsp;→ FSM 구조 및 Perception 기반의 AI 상태 제어  
&nbsp;&nbsp;&nbsp;→ 실시간 UI 반영을 위한 HUD 구조 설계  

<br>

## 📸 스크린샷
 (추후 업로드 예정)

## 🧑‍💻 Author
  **JellytoCodes** (Created as part of a 2025 semester-end solo project.)  
  **개발 기간** : 2025.05.09 ~ 2025.06.02  
  
  **Thanks To. 강상용 교수님**  
