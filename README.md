# Philosophers

- What is dining philosophers problem?
    
    1960년대에 운영체제의 동기화에 대한 고전적 문제를 설명하기 위해 제시되었다.
    
    테이블에 음식이 있고 철학자들의 왼쪽에는 음식을 먹는데 필요한 도구들이 하나씩 있다. 음식을 먹기 위해서는 양쪽에 있는 도구 2개가 필요하다.
    
    철학자들은 eating, sleeping, thinking 3가지 상태로 있을 수 있다. eating 이후에 sleeping 상태가 된다. 어느정도 시간 동안 sleeping을 하고 깨어나면 thinking 상태에 있는다. thinking 상태는 eating을 기다리는 동안 지속된다.
    
- Problem
    
    모든 철학자가 자신의 도구를 동시에 집었을 때, 아무도 자신의 양쪽에 있는 도구 2개 모두 들지 못하는 `교착상태`에 빠질 수 있다.
    
- Improvement
    1. 항상 도구의 수 보다 적은 철학자가 eating 상태에 돌입한다.
    2. 양쪽 철학자들이 eating 상태가 아닐 때, 양쪽에 있는 도구를 동시에 집어서 eating 상태에 돌입한다.
    3. i번째 철학자가 홀수라면 왼쪽에 있는 도구를, 짝수라면 오른쪽에 있는 도구를 들어서 eating 상태를 노린다.
    
    이와 같은 방법들이 동기화에서 `교착 상태`를 해결할 순 있지만, `기아 상태`를 해결하진 못한다. 철학자가 일정기간 동안 eating하지 못하면 굶어죽기 때문에 기아상태에 대한 해결도 필요하다.
    
- Considerations
    
    이런 문제와 같이 동기화에 대한 고전적 문제들이 시사하는 바는 다음과 같다.
    
    - ※ 동기화에 대한 고전적 문제들
        
        `Dining philosophers`
        
        `Consumer-Producer`
        
        `Readers-Writers`
        
    
    멀티 프로세싱 혹은 멀티 쓰레딩 기법이 이득을 가져다 주지만 자원을 공유하는 입장에서 동기화가 필수적으로 요구되고 그 과정에서 여러가지 고려해야할 요소들이 있다는 것을 알려준다.
    
    - 동기화에 요구되는 요소들⭐️
        1. Data consistency 가 확보되는가?
        2. Deadlock 이 발생하는가?
        3. Starvation 이 발생하는가?
        4. Concurrency 의 제공이 원할한가?
