fun main() {
    val aggs = generateSequence(::readLine).map(::parseLine).toList()
    val g = gather_graph(aggs)
    val c = gather_cardinalities(aggs)

    val ans = count_contained_recur(g, c, "shiny gold")
    println(ans)
}

private fun count_contained_recur(g: Map<String, List<String>>, c: Map<Pair<String, String>, Int>, u: String): Int {
    if (!g.containsKey(u)) return 0

    var ans = 0
    for (v in g[u]!!) {
        val factor = c[u to v]!!
        ans += factor
        ans += count_contained_recur(g, c, v) * factor
    }

    return ans
}

private fun gather_graph(aggs: List<Agg>): Map<String, List<String>> {
    val ans = mutableMapOf<String, List<String>>()

    for ((color, subs) in aggs) {
        val adj = subs.map { it.color }
        ans[color] = adj
    }

    return ans
}

private fun gather_cardinalities(aggs: List<Agg>): Map<Pair<String, String>, Int> {
    val ans = mutableMapOf<Pair<String, String>, Int>()

    for ((color, subs) in aggs) {
        for (sub in subs) {
            ans[color to sub.color] = sub.count
        }
    }

    return ans
}

private fun parseLine(line: String): Agg {
    if (line.endsWith(" bags contain no other bags.")) {
        return Agg(line.split(" bags ").first(), emptyList())
    }

    val g = Regex("^([a-z ]+) bags contain ([0-9a-z, ]+)\\.$").matchEntire(line)!!.groups
    val color = g[1]!!.value
    val subs = g[2]!!.value.split(", ").map(::parseSubText)

    return Agg(color, subs)
}

private fun parseSubText(text: String): Sub {
    val g = Regex("^(\\d+) ([a-z ]+) bag(s?)$").matchEntire(text)!!.groups
    return Sub(g[1]!!.value.toInt(), g[2]!!.value)
}

private data class Agg(val color: String, val subs: List<Sub>)
private data class Sub(val count: Int, val color: String)

private fun readLn() = readLine()!!
private fun readInt() = readLn().toInt()
private fun readLong() = readLn().toLong()
private fun readStrings() = readLn().split(" ")
private fun readInts() = readStrings().map(String::toInt)
private fun readLongs() = readStrings().map(String::toLong)
