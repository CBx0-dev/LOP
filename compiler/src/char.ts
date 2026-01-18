export function char_is_alpha(c: string): boolean {
    const charCode: number = c.charCodeAt(0);
    return (charCode >= 65 && charCode <= 90) || (charCode >= 97 && charCode <= 122);
}

export function char_is_numeric(c: string): boolean {
    const charCode: number = c.charCodeAt(0);
    return charCode >= 48 && charCode <= 57;
}

export function char_is_alpha_numeric(c: string): boolean {
    return char_is_alpha(c) || char_is_numeric(c);
}

export function char_is_whitespace(c: string): boolean {
    return c === ' ' || c === '\t' || c === '\n' || c === '\r';
}