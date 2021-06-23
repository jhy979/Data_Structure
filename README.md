# Data_Structure

자료구조에 대해 공부합니다.

여러 가지 복합적인 구조들에 대해 이해하고 알고리즘을 작성해보는 저만의 연습란입니다.<br>

> 수업시간에 과제로 진행한 부분도 있고, 자료구조를 연습하는 차원에서 머신러닝 관련 알고리즘들을 C로 작성해보기도 하였습니다.
___
## HW1 : Selection Sort
- 선택 정렬을 구현하여 n의 사이즈가 커질수록 프로그램의 동작 시간이 어느정도 걸리는지에 대하여 알아봤습니다.
- 알려진 시간복잡도와 일치하는지 csv파일로 추출하여 결과를 비교했습니다. 
___
## HW2 : KMP Algorithm
- KMP 알고리즘을 구현했습니다.
- 두 개의 string을 입력받아 pattern matching을 체크하여 input 문자열 속에 pattern이 나타나는지 여부를 반환합니다.
___
## HW3 : Infix To Postfix Linked Stacks Queues
- Infix 표기식을 Postfix 표기법으로 바꿔주는 프로그램입니다.

___
## HW4 : Matrix with linked list representation
- 행렬을 표현하는 방법에는 배열과 링크드 리스트 2가지가 있습니다.
- dense할 경우 배열도 좋지만 sparse할 경우 성능이 매우 안 좋습니다.
- 따라서 이를 해결하기 위해 Linked List로 행렬을 표현하는 방법에 대해 알아봤습니다.
___
## HW5 : Threaded Binary Trees
- 기존 Binary Tree 같은 경우 inorder traversal을 하기 위해 successor를 찾는 함수를 두어 다음 친구를 찾았어야했습니다.
- 그러나 Threaded Binary Tree 같은 경우는 right_thread, left_thread 포인터를 찾아 바로 자신의 상위 부모 혹은 root를 지칭하게 하여 바로바로 inorder traversal을 쉽게 할 수 있는 구조를 가지고 있습니다.
___
## Weighted KNN
- 대표적인 Clustering 알고리즘입니다.
- 데이터 분포가 2차원에 존재하고 있습니다
- 새로운 test 데이터가 들어왔을 때 이 데이터는 어느 클래스에 속하는지를 판단하는 문제입니다.
- 이를 거리를 가중치로 두어 Weighted KNN을 구현했습니다.
___
## K-Medoids Clustering
- K-Medoids Clustering은 주어진 데이터셋을 K개의 군집으로 묶는 clustering 알고리즘입니다.
- Clustering은 Class Label이 존재하지 않습니다.
> 1. 임시로 K개의 medoid가 될 데이터들을 주어진 데이터에서 임의로 선택합니다. 
> 2. 모든 데이터와 K개 각각의 medoids와의 거리를 계산하여 가장 가까운 medoid에 해당 데이터를 할당합니다.
> 3. 각 cluster에 대해 cluster 내 거리의 합이 최소화 되는 데이터를 찾아 그 데이터를 새로운 medoid로 업데이트합니다. 
> 4. 2단계, 3단계를 더 이상 군집 분류에 변화가 없거나 사용자가 정해놓은 maximum iteration 수에 도달할 때 까지 반복합니다.
