<template>
    <div v-if="posts.length > 0">
      <div class="row mt-4">
        <div class="col-2 h6">Chromosome</div>
        <div class="col-1 h6">TRNA name</div>
        <div class="col-4 h6">TRNA sequence</div>
        <div class="col-1 h6">Direction</div>
        <div class="col-1 h6">Start</div>
        <div class="col-1 h6">End</div>
        <div class="col-1 h6">E-value</div>
      </div>
          <PostItem 
              v-for="post in posts"
              :post="post"
              :key="post.id"
          />        
    </div>
    <div class="h4 my-5" v-else>
      List is empty
    </div>
    
</template>

<script>
import PostItem from '@/components/PostItem.vue';

export default {
  components: { PostItem },
  props: {
        posts: {
            type: Array,
            required: true,
        }
    },
}
</script>

<style scoped>

</style>