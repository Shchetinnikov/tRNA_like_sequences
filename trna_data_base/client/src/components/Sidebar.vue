<template>
    <div class="d-flex flex-column flex-shrink-0 p-3 text-white bg-secondary">
        <ul class="nav nav-pills flex-column mb-auto">
            <li class="nav-item" v-for="i in items.length">
                <div 
                    class="nav-link text-white btn_item" 
                    @click="goTo(urls[i - 1])"
                    :key="urls[i - 1]"
                    :class="{
                        'active': urls[i - 1] === this.current_item
                    }"
                >
                    {{ items[i - 1] }}
                </div>
            </li>
        </ul>
    </div>
</template>

<script>
export default {
    data() {
        return {
            items: ['Main overview', 'tRNA information', 'FASTA sequences', 'Help'],
            urls: ['/', '/info', '/seq', '/help'],
            current_item: ''
        }
    },
    methods: {
        goTo(url) {
            this.current_item = url;
            this.$router.push(url);
        }
    },
    mounted() {
        this.current_item = new URL(location.href).pathname
    }
}
</script>

<style scoped>
.btn_item {
    cursor: pointer;
}
</style>