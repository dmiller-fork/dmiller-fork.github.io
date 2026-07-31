    function parseUrl(url) {
      const u = new URL(url);
      const instance = u.hostname;
      const parts = u.pathname.split('/').filter(Boolean);
      const id = parts[parts.length - 1];
      if (!id || isNaN(id)) throw new Error('Could not parse post ID from URL — use the browser to get a valid URL');
      return { instance, id };
    }
    
    async function proxyFetch(url) { 
      const res = await fetch('https://fediproxy.com/proxy?url=' + encodeURIComponent(url));
      if (!res.ok) throw new Error('Fetch failed: ' + res.status);
      const data = await res.json();
      if (data.error) throw new Error('API error: ' + data.error);
      return data;
    }
    
    function renderPost(post, isReply = false) {
      const acct = post.account;
      const date = new Date(post.created_at).toLocaleString();
      return `
        <div class="post${isReply ? ' reply' : ''}">
          <div class="header">
            <img class="avatar" src="${acct.avatar}" alt="" />
            <div>
              <div class="name">${acct.display_name || acct.username}</div>
              <div class="handle">@${acct.acct}</div>
            </div>
          </div>
          <div class="content">${post.content}</div>
          <div class="meta">${date} &middot; ${post.replies_count} replies &middot; ${post.reblogs_count} boosts &middot; ${post.       favourites_count} favorites</div>
        </div>`;
    }
document.addEventListener("DOMContentLoaded", async function () {
    try {
        const instance = "theforkiverse.com";
        const base = `https://${instance}/api/v1/statuses/${id}`;

        const [post, context] = await Promise.all([
          proxyFetch(base),
          proxyFetch(base + '/context'),
        ]);

        const replies = context.descendants ?? [];
        const repliesHtml = replies.length
          ? `<div class="replies-label">${replies.length} repl${replies.length === 1 ? 'y' : 'ies'}</div>` + replies.map(r =>           renderPost(r, true)).join('')
          : '<p style="color:#999;font-size:13px">No replies yet.</p>';

        document.getElementById('comments').innerHTML = renderPost(post) + repliesHtml;
      } catch (err) {
        document.getElementById('error').textContent = err.message;
        document.getElementById('comments').innerHTML = '';
      }
    });
