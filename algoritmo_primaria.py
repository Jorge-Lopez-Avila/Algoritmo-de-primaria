def multiplicar_con_proceso(a: str, b: str) -> str:
    # --- Normalización y signo ---
    a = a.strip()
    b = b.strip()
    signo = 1
    if a.startswith('-'):
        signo *= -1
        a = a[1:]
    if b.startswith('-'):
        signo *= -1
        b = b[1:]
    a = a.lstrip('0') or '0'
    b = b.lstrip('0') or '0'

    # Caso directo si alguno es 0
    if a == '0' or b == '0':
        width = max(len(a) + len(b), 1)
        print()
        print(a.rjust(width))
        print(('x ' + b).rjust(width))
        print('-' * width)
        print('0'.rjust(width))
        print('-' * width)
        print('Resultado:', '0')
        return '0'

    len1, len2 = len(a), len(b)
    width = len1 + len2  # máximo de dígitos del producto
    resultado = [0] * width

    # --- Encabezado alineado a la derecha ---
    print()
    print(a.rjust(width))
    print(('x ' + b).rjust(width))
    print('-' * width)

    # --- Filas parciales (de derecha a izquierda en el multiplicador) ---
    for j in range(len2 - 1, -1, -1):
        d2 = ord(b[j]) - 48
        parcial = [0] * width
        shift = (len2 - 1) - j            # cuántos "ceros" a la derecha
        k = width - 1 - shift             # empezamos a escribir desde la derecha menos el shift
        carry = 0

        for i in range(len1 - 1, -1, -1):
            d1 = ord(a[i]) - 48
            prod = d1 * d2 + carry
            parcial[k] = prod % 10
            carry = prod // 10
            k -= 1
        if carry > 0 and k >= 0:
            parcial[k] = carry

        # imprimir fila parcial (sin ceros a la izquierda, pero alineada a 'width')
        s_parcial = ''.join(map(str, parcial)).lstrip('0') or '0'
        print(s_parcial.rjust(width))

        # sumar parcial al acumulado
        c = 0
        for p in range(width - 1, -1, -1):
            s = resultado[p] + parcial[p] + c
            resultado[p] = s % 10
            c = s // 10

    # --- Resultado final ---
    print('-' * width)
    res = ''.join(map(str, resultado)).lstrip('0') or '0'
    if signo < 0 and res != '0':
        res = '-' + res
    print('Resultado:', res)
    return res


# --- Ejecución interactiva ---
if __name__ == "__main__":
    n1 = input("Ingrese el primer numero: ")
    n2 = input("Ingrese el segundo numero: ")
    multiplicar_con_proceso(n1, n2)
