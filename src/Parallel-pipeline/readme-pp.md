# The parallel pipeline
This src dir contains three different components in a fair load balancing system. The `taskwork` and `taskworker2` components are responsible for computing a certain workload, fairly distributed to it by the `taskvent`(taskventilator). After the work is done, the `tasksink` sums the computational effort expanded by the taskworkers, and displays the total amount of effort to the end user of the system. To do this, it is necessary to run the three processes in three separate terminal tabs/windows.

## Clean termination
It is particularly important to stress the importance of shutting down the `taskworker2` and `taskwork` instances gracefully, using CTRL+C. Otherwise, they end up as zombie-processes and may lead to unintuitive results.
