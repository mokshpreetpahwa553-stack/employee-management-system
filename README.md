# employee-management-system
Employee Management System in C with enums, structs, sorting, bonus calculation, promotion logic, and department-wise analytics.

A console-based Employee Management System written in C that stores employee records, tracks projects, calculates bonuses, and generates department-wise statistics.

 Features

- Store detailed employee records:
  - Personal details: name, ID, department, joining year, salary
  - Employment status: FULL_TIME, PART_TIME, CONTRACT, INTERN
  - Performance rating: EXCELLENT, GOOD, SATISFACTORY, NEEDS_IMPROVEMENT, UNSATISFACTORY
  - Up to 5 projects per employee (name, status, budget, completion percentage)

- Sorting and organisation:
  - Sort employees by department (alphabetically)
  - Within each department, sort by performance rating
  - If performance is equal, sort by salary (higher first)

- Bonus calculation:
  - Performance-based bonus percentages (e.g. higher for EXCELLENT)
  - Multipliers based on employment status (e.g. FULL_TIME, PART_TIME)
  - Bonus stored per employee and printed with details

- Department-wise statistics:
  - Total project budget per department
  - Average salary per employment status in each department
  - Count of employees by performance rating in each department

- Project monitoring:
  - List employees working on ONGOING projects with completion < 50%
  - Group output by department

- Promotion recommendations:
  - Recommend employees for promotion if:
    - Performance is EXCELLENT or GOOD
    - Working on at least 2 COMPLETED projects
    - Tenure of at least 3 years
    - Employment status is FULL_TIME or PART_TIME

- Risk assessment:
  - Identify departments where more than 40% of employees have
    NEEDS_IMPROVEMENT or UNSATISFACTORY ratings.

Technologies Used

- Language: C
- Concepts used:
  - `struct` for EMPLOYEE and PROJECT
  - `enum` for employment status, performance rating, and project status
  - Arrays, loops, functions, and selection sort–style logic
  - String handling with `fgets`, `strcmp`, and `strcspn`
  - Basic use of `stdbool.h`

File

- `employee_management_system.c` – main source file containing:
  - Data type definitions (`EMPLOYEE`, `PROJECT`, enums)
  - Input functions for employees and projects
  - Sorting functions
  - Bonus calculation
  - Reporting/statistics functions
  - `main()` to orchestrate all functionality

## How to Compile and Run

Using `gcc`:

```bash
gcc employee_management_system.c -o employee_management_system
./employee_management_system
