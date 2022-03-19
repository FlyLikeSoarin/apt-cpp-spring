import os


with open('.students.txt', 'r') as f:
    students = f.readlines()

with open('.tasks.txt', 'r') as f:
    tasks = f.readlines()

paths = [f'./{s.lower().strip()}/{t.lower().strip()}' for s in students for t in tasks]
new_paths = list(filter(lambda path: not os.path.exists(path), paths))

print('Following directories will be created')
print(*new_paths, sep='\n')
reply = input('Proceed? Y/N' + ' (y/n): ').lower().strip()
if reply[:1] == 'y':
    for path in new_paths:
        os.makedirs(path)
if reply[:1] == 'n':
    pass
print('Done')