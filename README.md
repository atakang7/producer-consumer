This multithreaded C program addresses the "Smokers Problem" through the use of semaphores. It features an agent thread and three smoker threads. The agent is responsible for placing two distinct items on a table, enabling smokers to pick them up and proceed to smoke. Each smoker already has one of the three items: Tobacco, Paper, or Matches.

Semaphore synchronization ensures proper operation: the agent uses a semaphore, and each smoker has a unique semaphore. The agent waits on its semaphore to place items and subsequently signals the corresponding smoker semaphore. Smokers, in turn, wait for their semaphore to be signaled, allowing them to gather items, smoke, and then signal the agent semaphore.

The `agentfn` function, executed by the agent thread, manages item placement and smoker signaling. The `smokerfn` function, executed by smoker threads, handles item collection, smoking, and signaling the agent.

The `main` function sets up threads and semaphores and ensures program completion by joining threads.

Example output:
```
smokersproject on  master [?] via C v11.4.0-gcc 
❯ ./a.out 
Agent placing items Matches and Tobacco for the [smoker 1] which has [Paper]
Smoker 1 is smoking...
Agent placing items Matches and Tobacco for the [smoker 1] which has [Paper]
Smoker 1 is smoking...
Agent placing items Paper and Matches for the [smoker 0] which has [Tobacco]
Smoker 0 is smoking...
Agent placing items Matches and Tobacco for the [smoker 1] which has [Paper]
Smoker 1 is smoking...
Agent placing items Tobacco and Paper for the [smoker 2] which has [Matches]
Smoker 2 is smoking...
Smoker 2 is cancelling...
Smoker 0 is cancelling...
Smoker 1 is cancelling...
```

