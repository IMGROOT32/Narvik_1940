# Narvik 1940

> 역사 기반 싱글 FPS | Unreal Engine 5 / C++ | 개발 진행 중

## 프로젝트 개요
>장르 : 역사 기반 싱글 FPS
>플랫폼 : PC
>개발 형태 : 개인 프로젝트
>기간 : 14주
>담당 : 기획 + 개발 전체

## 담당 역할 - 기획 + 개발 전체

### Game System Architecture
>Mission / AI / Damage / Player 시스템 간 관계 설계

### AI System - 국가별 파라미터화
>독일(넓은 시야, 선공) / 영국(수류탄 중심) / 노르웨이(후공) 행동 차등화
>AI 행동 변수를 파라미터로 분리 -> 재사용 가능한 구조 설계

### Damage System - 부위별 데이터 구조
>Head, Chest, L/R Arm, L/R Leg 총 6개의 부위 독립 HP 설계
>부위별 패널티 시스템 -> 전투 전략 선택에 직접 영향
>'EBodyPart' Enum + 'FBodyPartHealth' Struct 기반 Data-Driven 설계

### Mission System
>15개 미션, 성공/실패 조건 분리
>3개 국가 X 동일 전투 X 다른 목표 구조 설계

## 기술 스택
'Unreal Engine 5', 'C++', 'AI Behavior Tree', 'Data-Driven Design'
