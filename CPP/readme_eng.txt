=============== DESCRIPTION ===============

Example consists:
1. OOP
2. Design patterns
3. Libraries boost (1.52) è stl
4. Using WinApi
5. Multythreading

=============== DEPENDENCIES+CONSTRAINTS ===============
1. Boost library
2. libboost_thread-vc100-mt-gd-1_52.lib
3. Threads max = [CPU kernels count] õ [ThreadsPerKernel( = 10, declared in cThreadPool.cpp)]

=============== DETALIZATION ===============
1. cTaskGenerator - generates random tasks and run them into cThreadPool
2. cThreadPool - thread pool. Looking for tasks and run them. 
3. cThreadPool - create or resume threads for nes tasks.
4. cTask - abstract task (absrtact class). 
5. cTaskParams - common params for the tasks; includes callback function