import json

def parse_action(action: any) -> str:
    actionType = action['type']
    args = action['args']

    if actionType == 'move':
        try:
            return f'move({int(args["distance"])}, {int(args["velocity"])})'
        except ex:
            raise ValueError(f'not all arguments (distance, velocity) were accounted for in current args: {args}')
    elif actionType == 'turn':
        try:
            return f'turn({int(args["angle"])}, {int(args["velocity"])})'
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

with open('out.cpp', 'w') as f:
    f.write('\n'.join(results))
