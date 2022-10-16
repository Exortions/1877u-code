import json

def parse_action(action: any) -> str:
    actionType = action['type']
    args = action['args']

    if actionType == 'move':
        try:
            return f'move({int(args["distance"])}, {int(args["velocity"])});'
        except ex:
            raise ValueError(f'not all arguments (distance, velocity) were accounted for in current args: {args}')
    elif actionType == 'turn':
        try:
            return f'turn({int(args["angle"])}, {int(args["velocity"])});'
        except ex:
            raise ValueError(f'not all arguments (angle, velocity) were accounted for in current args: {args}')
    raise ValueError(f'invalid action type: {actionType}')

def parse_json() -> any:
    with open('input.json') as f:
        return json.loads(f.read())

parsed = parse_json()
actions = parsed['actions']

print(f'Parsing...\n  - {actions}\n\n')

results = []

for action in actions:
    print('Parsing action...')

    res = parse_action(action)

    results.append(res)

    print(f'Result: {res}\n')

with open('../src/generated-auton.cpp', 'w') as f:
    auton = '\n  '.join(results)

    code = '#include "generated-auton.h"\n#include "actions.h"\n#include "auton.h"\n\nvoid generated_auton() {\n  ' + auton + '\n}'

    f.write(code)
