fun main() {
    repeat(readInt()) {
        val (n, a, b) = readInts()
        assert(b <= Math.min(26, a))
        println(constructString(n, b))
    }
}

private fun constructString(n: Int, b: Int): String {
    val pattern = ('a'..('a' + b - 1)).joinToString("")
    val pref = pattern.repeat(n / b);
    val suff = pattern.substring(0, n % b);
    return pref + suff;
}

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
