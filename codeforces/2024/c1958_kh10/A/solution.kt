fun minOnes(n: Int): Int {
    var result = 100
    for (k3 in 0..40) {
        for (k5 in 0..25) {
            val x = k3 * 3 + k5 * 5
            if (x > n) break
            result = minOf(result, n - x)
        }
    }
    return result
}

fun main() {
    repeat(readInt()) {
        val n = readInt()
        println(minOnes(n))
    }
}

private fun readLn() = readLine()!!

private fun readInt() = readLn().toInt()
