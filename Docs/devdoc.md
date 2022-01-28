# 오픈월드(지향) 게임
 
- 키워드 : 백뷰,  RPG,  상호작용
- 사용 엔진 : 언리얼
- 참여자 : 류한진
- 컨셉 상세 : 
  - GameplayTag와 GameplayAttribute 적극 활용
  - 이를 기반으로 GameplayAbility와 AbilityTask 사용하는 유연한 게임 개발

## 핵심 요소 - 2주

- 전체 구조	12/27
  - SaveGame
  - 리플리케이션 상정
  - GameFramework 추종 모듈화
- 월드, 전투	12/28 ~ 12/30 
  - v 공통
  - v 이동, 공격, 점프
  - v 플레이어
  - 상호작용
  - 적
  - AI
- 아이템		12/31 ~ 1/3
  - 인벤토리
  - 드랍, 획득, 사용, 장착
- 내러티브		1/4 ~ 1/6
  - 다이얼로그
  - 대화
  - 컷씬?


## 준 핵심 요소 - 1주

- 퀘스트		1/7 ~ 1/11
  - 진행도(개별)
  - 진행도(전체)
  - 연계
  - 보상
- 액션		1/12 ~ 1/13
  - 특수 스킬
  - 폭탄
  - 활
  - v 달리기, 구르기, 덤블링 등
- 상호작용		1/14
  - 간단한 상점


## 부가 요소 – 1주

- 아이템 응용	TBD
  - 조합
  - 던지기
- 지형변경		TBD
  - 생성
  - 파괴
- 동적 레벨 로딩	TBD
  - 프리미티브 레벨 or 자동 생성
- 멀티플레이	TBD
  - Unreal GameFramework


## 기타

- 사용 에셋
  - 실사풍
    - 구하기 쉬움 (언리얼 주력 분야)
    - 인피니티 블레이드
    - 파라곤
    - 퀵셀, 메가플랜트

- 게임 목표
  - ? - 메인퀘스트의 부여, 완료
    - ! - 특정 아이템의 획득
    - ! - 특정 몬스터의 사냥
    - ? - 서브 퀘스트의 완료

- 언리얼 기능
  - Navmesh
  - Data Driven
  - Persistence Level
  - Sun and Sky
  - Gameplay Ability
  - Gameplay Tags
  
  
  
  
  
  ## Crunch
    - To Do
	  - 전투1		추적, 공격, 스킬, TakeDamage
	  - 전투2		Attribute, Effect, Ability, Tag
	  - 아이템		ItemIdeal, ItemActor, ItemInstance
	  - 저장		GameState, PlayerState
	  - 지형변경	Voxel
	  - UI		체력바, 타이틀, 사망, 엔딩
	  - 시네마틱	연출추가, 이펙트, 사운드
	  - 퀘스트		??