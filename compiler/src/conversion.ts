import {Binder, BoundNode, Type, type_eq_type} from "./binder";

export enum ConversionKind {
    IMPLICIT,
    EXPLICIT
}

export interface ConversionRules {
    from: Type;
    to: Type;
    kind: ConversionKind;
}

export interface Conversion {
    rules: ConversionRules[];
}

export function rule_init(from: Type, to: Type, kind: ConversionKind): ConversionRules {
    return {
        from,
        to,
        kind
    };
}

export function conversion_init(i8Type: Type,
                                i16Type: Type,
                                i32Type: Type,
                                i64Type: Type,
                                u8Type: Type,
                                u16Type: Type,
                                u32Type: Type,
                                u64Type: Type,
                                boolType: Type,
                                charType: Type): Conversion {
    return {
        rules: [
            rule_init(i8Type, i16Type, ConversionKind.IMPLICIT),
            rule_init(i16Type, i32Type, ConversionKind.IMPLICIT),
            rule_init(i32Type, i64Type, ConversionKind.IMPLICIT),

            rule_init(i16Type, i8Type, ConversionKind.EXPLICIT),
            rule_init(i32Type, i16Type, ConversionKind.EXPLICIT),
            rule_init(i64Type, i32Type, ConversionKind.EXPLICIT),

            rule_init(u8Type, u16Type, ConversionKind.IMPLICIT),
            rule_init(u16Type, u32Type, ConversionKind.IMPLICIT),
            rule_init(u32Type, u64Type, ConversionKind.IMPLICIT),

            rule_init(u16Type, u8Type, ConversionKind.EXPLICIT),
            rule_init(u32Type, u16Type, ConversionKind.EXPLICIT),
            rule_init(u64Type, u32Type, ConversionKind.EXPLICIT),

            rule_init(i64Type, boolType, ConversionKind.EXPLICIT),
            rule_init(u64Type, boolType, ConversionKind.EXPLICIT),

            rule_init(boolType, i8Type, ConversionKind.EXPLICIT),
            rule_init(boolType, u8Type, ConversionKind.EXPLICIT),

            rule_init(charType, u8Type, ConversionKind.IMPLICIT),
            rule_init(charType, i16Type, ConversionKind.IMPLICIT),
        ]
    };
}

export function conversion_classify(binder: Binder, from: Type, to: Type, explicit: boolean): ConversionRules[] | null {
    if (type_eq_type(from, to)) {
        return [];
    }

    // Type <--> Object
    if (from.definition && from.definition.type == BoundNode.TYPE_MEMBER && type_eq_type(to, binder.objectType)) {
        return [
            rule_init(from, to, ConversionKind.IMPLICIT),
        ];
    } else if (explicit && type_eq_type(from, binder.objectType) && to.definition && to.definition.type == BoundNode.TYPE_MEMBER) {
        return [
            rule_init(from, to, ConversionKind.EXPLICIT),
        ];
    } else
        // Enum Field <--> i32
    if (from.definition && from.definition.type == BoundNode.ENUM_MEMBER && type_eq_type(to, binder.i32Type)) {
        return [
            rule_init(from, to, ConversionKind.IMPLICIT),
        ];
    } else if (explicit && type_eq_type(from, binder.i32Type) && to.definition && to.definition.type == BoundNode.ENUM_MEMBER) {
        return [
            rule_init(from, to, ConversionKind.EXPLICIT),
        ];
    }

    let frontierTypes: Type[] = [from];
    let frontierPaths: ConversionRules[][] = [[]];

    while (frontierTypes.length > 0) {
        const nextTypes: Type[] = [];
        const nextPaths: ConversionRules[][] = [];

        for (let i: number = 0; i < frontierTypes.length; i++) {
            const currentType: Type = frontierTypes[i];
            const currentPath: ConversionRules[] = frontierPaths[i];

            for (const rule of binder.conversion.rules) {
                if (rule.from != currentType ||
                    !explicit && rule.kind == ConversionKind.EXPLICIT) {
                    continue;
                }

                let seen: boolean = false;
                for (const step of currentPath) {
                    if (step.from == rule.to) {
                        seen = true;
                        break;
                    }
                }

                if (seen) {
                    continue;
                }

                const newPath: ConversionRules[] = currentPath.concat(rule);

                if (rule.to == to) {
                    return newPath;
                }

                nextTypes.push(rule.to);
                nextPaths.push(newPath);
            }
        }

        frontierTypes = nextTypes;
        frontierPaths = nextPaths;
    }

    return null;
}