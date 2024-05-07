fun evaluate(src: String): Int {
    if (src == "M") return 0
    if (src.endsWith("S")) return -src.length
    return src.length
}

fun relationSymbol(x: Int, y: Int): Char {
    if (x == y) return '='
    return if (x < y) '<' else '>'
}

fun main() {
    repeat(readInt()) {
        val (x, y) = readStrings()
        println(relationSymbol(evaluate(x), evaluate(y)))
    }
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readStrings() = readLn().split(" ")
